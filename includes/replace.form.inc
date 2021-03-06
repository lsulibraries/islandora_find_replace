<?php

/**
 * @file
 * Form functions for the form to select which objects to update.
 */

/**
 * Form function to generate the table select for objects to operate on.
 *
 * @param array $form
 *   The form array.
 * @param array $form_state
 *   The form state array.
 * @param array $find_replace
 *   The find & replace database row.
 *
 * @return array
 *   The populated form array.
 */
function islandora_find_replace_replace_form($form, &$form_state, $find_replace) {
  module_load_include('inc', 'islandora_find_replace', 'includes/language');
  if ($find_replace['state'] != 'search') {
    drupal_set_message(t('There was a problem loading the submission.'), 'error');
    drupal_goto('admin/islandora/tools/find-replace/find');
  }

  $form_state['storage']['find_replace'] = $find_replace;
  $diff_exists = module_exists('islandora_pretty_text_diff');
  $options = array();
  $dsid = $find_replace['dsid'];

  foreach (unserialize($find_replace['find_results']) as $option) {
    $options[$option['object']] = array(
      'label' => l($option['label'], 'islandora/object/' . $option['object'],
        array('attributes' => array('target' => '_blank'))),
      'datastream' => l($dsid,
        'islandora/object/' . $option['object'] . '/datastream/' . $dsid . '/view',
        array('attributes' => array('target' => '_blank'))
      ),
      'count' => $option['count'],
    );
    if ($diff_exists) {
      $options[$option['object']]['preview'] = l(t('Preview'),
        'admin/islandora/tools/find-replace/replace/' . $find_replace['id'] . '/' . $option['object'] . '/preview',
        array('attributes' => array('target' => '_blank')));
    }
  }

  $header = array(
    'label' => t('Label'),
    'datastream' => t('Current Datastream content'),
    'count' => t('Number of occurrences'),
  );
  if ($diff_exists) {
    $header['preview'] = t('Preview Diff');
  }
  $form['process_all'] =  array(
    '#type' => 'checkbox',
    '#title' => t('Process All'),
    '#description'=> t('Check here to process all results'),
  );

  if (count($options)) {
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Replace String'),
    );
  }
  $form['back'] = array(
    '#type' => 'markup',
    '#markup' => l(t('Back (New Search)'), 'admin/islandora/tools/find-replace/find'),
  );
  $count = (string) count(unserialize($find_replace['find_results']));
  $form['total'] = array(
    '#type' => 'markup',
    '#markup' => "<p>Total number of items that match search: $count</p>",
  );
  $php_max_input_vars = ini_get('max_input_vars');
  $form['process_all'] = array(
    '#type' => 'checkbox',
    '#title' => lang('selcheckbox'),
  );

  if (count($options)) {
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Replace String'),
    );
  }

  $form['preview'] = array(
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $options,
    '#empty' => l(t('No matching objects were found. Search again.'),
      'admin/islandora/tools/find-replace/find'),
    '#attributes' => array('class' => array('form-checkbox', 'in_tableselect')),
  );

  $max_input_vars = array(
    "maxInputVars" => $php_max_input_vars,
  );
  $path = drupal_get_path('module', 'islandora_find_replace') . '/js/islandora_find_replace.js';
  drupal_add_js(array("islandora_find_replace" => $max_input_vars), "setting");
  $form['#attached']['js'][] = array(
    'data' => $path,
    'type' => 'file',
    'scope' => 'footer',
  );

  return $form;
}

/**
 * Form submit function for the replace form.
 *
 * @param array $form
 *   The form array.
 * @param array $form_state
 *   The form state array.
 */
function islandora_find_replace_replace_form_submit($form, &$form_state) {
  $selected = $form_state['values']['process_all'] ?
    array_keys($form_state['values']['preview']) :
    array_keys(array_filter($form_state['values']['preview']));

  $operations = array();
  foreach ($selected as $select) {
    $operations[] = array('islandora_find_replace_update_objects', array(
      $select,
      $form_state['storage']['find_replace']['dsid'],
      $form_state['storage']['find_replace']['find'],
      $form_state['storage']['find_replace']['replacement'],
      $form_state['storage']['find_replace']['isregex'],
      $form_state['storage']['find_replace']['id']),
    );
  }
  $batch = array(
    'operations' => $operations,
    'title' => t('Replacing Text'),
    'init_message' => t('Beginning text replacement.'),
    'finished' => 'islandora_find_replace_update_complete',
    'progress_message' => t('Processed @current out of @total.'),
  );
  batch_set($batch);
  $form_state['redirect'] = 'admin/islandora/tools/find-replace/log/' . $form_state['storage']['find_replace']['id'];
}
