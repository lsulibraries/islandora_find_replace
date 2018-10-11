<?php
function islandora_find_replace_admin_form($form, &$form_state) {
  $form['language'] = array(
    '#type' => 'fieldset',
    '#title' => 'Language strings',
    '#tree' => TRUE,
  );
  module_load_include('inc', 'islandora_find_replace', 'includes/language');
  $strings = islandora_find_replace_language();
  $required = array('pageHeader', 'ect',  );
  foreach ($strings as $key => $str) {
    foreach($required) {
      if ($key == $req) {
        $form[$key]['languagechose'] = array(
          '#title' => t('Is this field required??'),
          '#type' => 'checkbox',
        );

      }
    }
    $form[$key]['language'] = [
      '#title' => $str['title'],
      '#default_value' => variable_get("islandora_find_replace_language_$key", $str['default']),
      '#type' => isset($str['type']) ? $str['type'] : 'textfield',
    ];
     }
     dpm($form);
  return $form;
}

function islandora_find_replace_admin_form_validate() {

}
