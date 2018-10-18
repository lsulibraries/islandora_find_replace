<?php

function islandora_find_replace_admin_form($form, &$form_state) {
  $form['language'] = array(
    '#type' => 'fieldset',
    '#title' => 'Language strings',
    '#tree' => TRUE,
  );
  module_load_include('inc', 'islandora_find_replace', 'includes/language');
  $strings = islandora_find_replace_language();
  $required = array('contentmodel', 'namespace', 'collection');
  foreach ($strings as $key => $str) {
    foreach($required as $req) {
      if ($key == $req) {
        $form["language_choose_$key"] = array(
          '#title' => t('Require this field?'),
          '#type' => 'checkbox',
          '#description' => t(' Pick one or more.'),
          '#default_value' => variable_get("language_choose_$key", FALSE),
        );
      }
    }
    $form[$key]['language'] = [
      '#title' => $str['title'],
      '#default_value' => variable_get("islandora_find_replace_language_$key", $str['default']),
      '#type' => isset($str['type']) ? $str['type'] : 'textfield',
    ];
     }
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  return $form;
}

function islandora_find_replace_admin_form_validate($form, &$form_state) {
  $required = array('contentmodel' => 0, 'namespace' => 0, 'collection' => 0);
  foreach ($required as $string => $set) {
    $required[$string] = $form_state['complete form']["language_choose_$string"]['#value'];
  }
  if (!in_array('1', $required)) {
    drupal_set_message("you must pick one of the first three checkboxes. Content Model set to required by default.",'error');

  }
  else {
    dsm('Updated');
  }
}

function islandora_find_replace_admin_form_submit($form, &$form_state) {
$required = array('contentmodel', 'namespace', 'collection');
$test = 0;
foreach($required as $req){
   if($form["language_choose_$req"]['#value'] == true){
     variable_set("language_choose_$req", true);
     $test += 1;
   }
   else{
     variable_set("language_choose_$req", false);
   }
 }
 if ($test < 1) {
   variable_set("language_choose_contentmodel", true);
 }
}
