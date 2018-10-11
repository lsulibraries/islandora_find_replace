<?php
function islandora_find_replace_language()
{
  return [
    'pageHeader' => [
      'title' => 'Form Title',
      'default' => ('Find objects'),
    ],
    'contentmodel' => [
      'title' => 'Content Model',
      'default' => t('Limit the search to objects with the selected content model.'),
    ],
    'namespace' => [
      'title' => t('Namespace'),
      'default' => t('A single namespace to search for the string.'),
    ],
    'collection' => [
      'title' => t('Collection'),
      'default' => t('Limit the search to objects directly in the selected collection.'),
    ],
    'datastream' => [
      'title' => t('Datastream ID'),
      'default' => t('A single datastream ID (DSID) to search for the string.'),
    ],
    'search' => [
      'type' => 'textarea',
      'title' => t('Search Text'),
      'default' => t('The text to search for in the datastream. Special characters must be escaped.'),
    ],
    'replacemnt' => [
      'type' => 'textarea',
      'title' => t('Search Text'),
      'default' => t('The text to replace the search with. Special characters must be escaped. Use (empty) to replace the search text with nothing.
'),
    ],
    'reg_exp_pattern' => [
    'title' => t('preg_match pattern'),
    'default' => t('The regular expresion to evaluate in the datastream.'),
    ],
    'reg_exp_replace' => [
    'title' => t('preg_match replacement'),
    'default' => t('The replacement expression against your matched pattern.'),
    ],
  ];
}

function lang($key) {
  $fullkey = "islandora_find_replace_language_$key";
  $val = variable_get($fullkey);
  if (!$val) {
    $values = islandora_find_replace_language();
    if (!array_key_exists($key, $values)) {
      return '[missing string key]';
    }
    return $values[$key]['default'];
  }
  return $val;
}
