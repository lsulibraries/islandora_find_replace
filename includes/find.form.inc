<?php

/**
 * @file
 * Form functions for the form to find objects to operate on.
 */

/**
 * The form function for the form to find objects to operate on.
 *
 * @param array $form
 *   The form array.
 * @param array $form_state
 *   The form state array.
 *
 * @return array
 *   The built form array.
 */
function islandora_find_replace_find_form($form, &$form_state) {
  module_load_include('inc', 'islandora', 'includes/utilities');
  module_load_include('inc', 'islandora_find_replace', 'includes/language');
  $form = array();

  $form['find'] = array(
    '#type' => 'fieldset',
    '#title' => lang('pageHeader'),
    '#description' => lang('pageheaderdesc'),
  );

  $content_models = islandora_get_content_models();
  $cmodel_options = array();
  foreach ($content_models as $model) {
    $cmodel_options[$model['pid']] = check_plain($model['label']);
  }

  $form['find']['content_model'] = array(
    '#type' => 'select',
    '#title' => lang('contentmodel'),
    '#description' => lang('contentdesc'),
    '#options' => $cmodel_options,
    '#required' => variable_get('language_choose_contentmodel', FALSE),
    '#empty_option' => t(' - Select -'),
  );
  $form['find']['namespace'] = array(
    '#type' => 'textfield',
    '#title' => lang('namespace'),
    '#description' => lang('namespacedesc'),
    '#required' => variable_get('language_choose_namespace', FALSE),
  );
  $collections = islandora_basic_collection_get_collections();
  $collection_options = array();
  foreach ($collections as $collection) {
    $collection_options[$collection['pid']] = check_plain($collection['label']) . ' - (' . $collection['pid'] . ')';
  }
  $form['find']['collection'] = array(
    '#type' => 'select',
    '#title' => lang('collection'),
    '#description' => lang('collectiondesc'),
    '#options' => $collection_options,
    '#required' => variable_get('language_choose_collection', FALSE),
  );

  $form['find']['date'] = array(
    '#type' => 'fieldset',
    '#title' => t('Date Condition'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['find']['date']['date_property'] = array(
    '#type' => 'select',
    '#title' => t('Date Condition'),
    '#options' => array(
      '' => t('- Select -'),
      'createdDate' => t('Date Created'),
      'lastModifiedDate' => t('Date Modified'),
    ),
    '#description' => t('To limit by date, select a date property.'),
  );

 $form['find']['date']['date_from'] = array(
    '#type' => 'date',
    '#title' => t('Date From'),
    '#description' => t('The start date for the date property selected above (inclusive).'),
  );
  $form['find']['date']['date_to'] = array(
    '#type' => 'date',
    '#title' => t('Date To'),
    '#description' => t('The end date for the date property selected above (inclusive).'),
  );

  $form['dsid'] = array(
    '#type' => 'textfield',
    '#title' => lang('datastream'),
    '#description' => lang('datastreamdesc'),
    '#required' => TRUE,
  );

  $path = l("regular expression syntax documentation for PHP","http://php.net/manual/en/reference.pcre.pattern.syntax.php");
  $form['regex'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use a regular expression'),
    '#description' => t("See $path"),
    '#required' => FALSE,
    '#checked' => 0,
    '#return_value' => 1,
    '#default_value' => 0,
  );

  $form['preg_pattern'] = array(
    '#type' => 'textarea',
    '#title' => lang('reg_exp_pattern'),
    '#description' => lang('reg_exp_pattern_desc'),
    '#rows' => 1,
    '#states' => array(
      'required' => array(
        ':input[name="regex"]' => array('checked' => TRUE),
       ),
       'invisible' => array(
         ':input[name="regex"]' => array('checked' => FALSE),
       ),
    ),
  );

  $form['preg_replacement'] = array(
    '#type' => 'textarea',
    '#title' => lang('reg_exp_replace'),
    '#description' => lang('reg_exp_replace_desc'),
    '#rows' => 1,
    '#states' => array(
      'required' => array(
        ':input[name="regex"]' => array('checked' => TRUE),
       ),
       'invisible' => array(
         ':input[name="regex"]' => array('checked' => FALSE),
       ),
    ),
  );


  $form['search'] = array(
    '#type' => 'textarea',
    '#title' => lang('search'),
    '#description' => lang('searchdesc'),
    '#rows' => 1,
    '#states' => array(
      'required' => array(
        ':input[name="regex"]' => array('checked' => FALSE),
      ),
      'invisible' => array(
        ':input[name="regex"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['replace'] = array(
    '#type' => 'textarea',
    '#title' => lang('replacement'),
    '#description' => lang('replacemntdesc'),
    '#rows' => 1,
    '#states' => array(
      'required' => array(
        ':input[name="regex"]' => array('checked' => FALSE),
      ),
      'invisible' => array(
        ':input[name="regex"]' => array('checked' => TRUE),
      ),
    ),
  );


  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Find objects'),
  );

  return $form;
}

/**
 * Find form validation function.
 *
 * @param array $form
 *   The form array.
 * @param array $form_state
 *   The form state array.
 */
function islandora_find_replace_find_form_validate($form, &$form_state) {
  $val = $form_state['values'];
  $disallowed_dsids = array(
    'RELS-EXT',
    'RELS-INT',
    'POLICY',
    'COLLECTION_POLICY',
  );
  if (in_array(strtoupper(trim($val['dsid'])), $disallowed_dsids)) {
    form_set_error('dsid', t('Modifications are not permitted for the selected Datastream ID.'));
  }
  if ($val['date_property']) {
    $from = _islandora_find_replace_timestamp_from_form_date($val['date_from']);
    $to = _islandora_find_replace_timestamp_from_form_date($val['date_to'], FALSE);
    if ($from > $to) {
      form_set_error('date_from', t('The Date From cannot be after the Date To.'));
    }
  }
  if ($val['regex'] == 1) {
    $regexerror = false;
    // Verify that pattern starts and ends with
    try {
      $matches = preg_replace($val['preg_pattern'], $val['preg_replacement'], '');
      $regexerror =  $matches === NULL ? true: false;
    }
    catch(Exception $e) {
      $regexerror = true;
    }
    if ($regexerror) {
       form_set_error('preg_pattern', t('Please check your regex pattern for errors'));
       form_set_error('preg_replacement', t('Please check your regex replacement for errors'));
    }
  }
}

/**
 * Find form submit function.
 *
 * @param array $form
 *   The form array.
 * @param array $form_state
 *   The form state array.
 */
function islandora_find_replace_find_form_submit($form, &$form_state) {
  $candidates = islandora_find_replace_query($form_state['values']['content_model'],
    $form_state['values']['collection'],
    $form_state['values']['date_property'],
    $form_state['values']['date_from'],
    $form_state['values']['date_to'],
    $form_state['values']['namespace']
  );


  $isregex = $form_state['values']['regex'];
  $searchfor = !$isregex ? $form_state['values']['search'] : $form_state['values']['preg_pattern'];
  $replacewith = !$isregex ? $form_state['values']['replace'] : $form_state['values']['preg_replacement'];
  $find_replace = array(
    'cmodel' => $form_state['values']['content_model'],
    'collection' => $form_state['values']['collection'],
    'namespace' => trim($form_state['values']['namespace']),
    'dsid' => $form_state['values']['dsid'],
    'find' => $searchfor,
    'replacement' => $replacewith,
    'isregex' => $isregex ,
    'state' => 'submitted',
  );
  if (empty($candidates)) {
    $form_state['rebuild'] = true;
    drupal_set_message(t('Sorry, no matching candidates found to which to search against. Please try another combination'),'status');
    return;
  }
  drupal_write_record('islandora_find_replace', $find_replace);

  $operations = array();
  foreach ($candidates as $candidate) {
    $operations[] = array(
      'islandora_find_replace_get_targets',
      array(
        $candidate,
        $form_state['values']['dsid'],
        $searchfor,
        $isregex,
        $find_replace['id'],
      ),
    );
  }

 $batch = array(
    'operations' => $operations,
    'title' => t('Finding Matching Objects'),
    'init_message' => t('Beginning search for matching objects.'),
    'finished' => 'islandora_find_replace_find_complete',
    'progress_message' => t('Processed @current out of @total.'),
  );

  batch_set($batch);
  $form_state['redirect'] = 'admin/islandora/tools/find-replace/replace/' . $find_replace['id'];
}
