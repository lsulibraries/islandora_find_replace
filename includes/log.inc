<?php

/**
 * @file
 * Callbacks to display a log of a find & replace operation.
 */

/**
 * Page callback to display a log of a find & replace operation.
 *
 * @param array $find_replace
 *   The Find & Replace database row as array.
 *
 * @return array
 *   Render array for page.
 */
function islandora_find_replace_operation_log($find_replace) {
  if ($find_replace['state'] != 'complete') {
    drupal_set_message(t('The Find & Replace log is not available.'), 'error');
    drupal_goto('admin/islandora/tools/find-replace/find');
  }

  $revisions = unserialize($find_replace['revisions']);
  $dsid = $find_replace['dsid'];

  $diff_exists = module_exists('islandora_pretty_text_diff');
  $success_header = array(
    t('Label'),
    t('PID'),
    t('Datastream Versions'),
  );
  if ($diff_exists) {
    $success_header[] = t('Datastream Diff');
  }

  $success_rows = array();
  foreach ($revisions['success'] as $pid => $info) {
    $object = islandora_object_load($pid);
    $success_rows[$pid] = array(
      l($object->label, 'islandora/object/' . $object->id,
        array('attributes' => array('target' => '_blank'))),
      t($pid),
      l($dsid, 'islandora/object/' . $object->id . '/datastream/' . $dsid . '/version',
        array('attributes' => array('target' => '_blank'))),
    );
    if ($diff_exists) {
      try {
        $history = $object->repository->api->m->getDatastreamHistory($object->id, $dsid);
        $before_version = islandora_find_replace_get_version_id($history, $info['before']);
        $after_version = islandora_find_replace_get_version_id($history, $info['after']);
        if (!is_null($before_version) && !is_null($after_version)) {
          $success_rows[$pid][] = l(
            t('View Diff'),
            "islandora/object/{$object->id}/datastream/{$dsid}/diff/{$before_version}/{$after_version}",
            array('attributes' => array('target' => '_blank'))
          );
        }
        else {
          $success_rows[$pid][] = t('Not available');
        }
      }
      catch (Exception $e) {
        $success_rows[$pid][] = t('Not available');
      }
    }
  }

  $fail_output = '';
  if (isset($revisions['fail']) && count($revisions['fail'])) {
    $fail_output = t('<h2>Failed Replacements</h2>');
    $fail_header = array(
      t('Label'),
      t('Datastream Versions'),
    );
    $fail_rows = array();
    foreach ($revisions['fail'] as $fail_pid) {
      $object = islandora_object_load($fail_pid);
      $fail_rows[$fail_pid] = array(
        l($object->label, 'islandora/object/' . $object->id,
          array('attributes' => array('target' => '_blank'))),
        l($dsid, 'islandora/object/' . $object->id . '/datastream/' . $dsid . '/version',
          array('attributes' => array('target' => '_blank'))),
      );
    }
    $fail_output .= theme('table', array('header' => $fail_header, 'rows' => $fail_rows));
  }
  $output= array();
  $output['csv_download'] = drupal_get_form('log_dl_form');
  $output['revert'] = drupal_get_form('revert_form');

  $output['success'] = array(
    '#type' => 'markup',
    '#markup' => t('<h2>Successful Replacements</h2>') . theme('table',
      array('header' => $success_header, 'rows' => $success_rows)),
  );


  if (!empty($fail_output)) {
    $output['fail'] = array(
      '#type' => 'markup',
      '#markup' => $fail_output,
    );
  }

  return $output;
}

function get_id_from_path() {
  $test = explode('/',$_GET['q']);
  $id = '';
  if(gettype((int)$test['5']) == 'integer'){
    $id = $test['5'];
  }
  return $id;
}

function get_revisions($id) {
  $current_log = db_query("SELECT MAX(:id) from {islandora_find_replace}",array(':id' => $id));
  $log_id = $current_log->fetchField();
  $query = db_query('SELECT revisions FROM {islandora_find_replace} WHERE id=' . '\'' .$log_id . '\'');
  return $query;
}

function download_pid_csv(){
  $id = get_id_from_path();
  $query = get_revisions($id);
  $csv = implode(',', unchunk_query($query));
  $filename = file_unmanaged_save_data($csv, "temporary://" . 'find_replace.csv', FILE_EXISTS_RENAME);
  $headers = [
    'Content-type' => 'text/csv; utf-8',
    'Content-Dispositon' => 'attachment; filename=islandora_find_replace_results.csv'
  ];
  file_transfer($filename, $headers);
}

function log_dl_form($form, &$form_state) {
  $form['csv_download'] = array(
     '#type' => 'submit',
     '#value' => 'Download CSV of PIDS',
     '#submit' => array('download_pid_csv'),
  );
 return $form;
}

function unchunk_query($query) {
  foreach ($query as $result) {
    $chunks = unserialize($result->revisions);
    $changed  = array_keys($chunks['success']);
    return $changed;
  }
}

function revert_find_replace() {
  $id = get_id_from_path();
  $query = get_revisions($id);
  $csv = unchunk_query($query);
  $operations = array();
  foreach ($csv as $pid) {
    $operations[] = array(
      'islandora_revert_datastream',
      array(
        $pid,
      ),
    );
  }

  $batch = array(
    'operations' => $operations,
    'title' => t('Revert each object'),
    'init_message' => t('Beginning revert.'),
    'finished' => 'islandora_find_replace_find_complete',
    'progress_message' => t('Processed @current out of @total.'),
  );

  batch_set($batch);
}

function revert_form($form, &$form_state) {
  $form['revert'] = array(
    '#type' => 'submit',
    '#value' => 'Revert this batch',
    '#submit' => array('revert_find_replace'),
  );
  return $form;
}

/**
 * Get the datastream's version ID based on a recorded datastream location.
 *
 * @param array $history
 *   A history of the datastream's modifications.
 * @param string $location
 *   The Fedora datastream location.
 *
 * @return int|null
 *   Return NULL if the version ID can't be found.
 */
function islandora_find_replace_get_version_id($history, $location) {
  foreach ($history as $version => $ds) {
    if ($ds['dsLocation'] == $location) {
      return $version;
    }
  }
  return NULL;
}
