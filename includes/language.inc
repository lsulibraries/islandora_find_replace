<?php
function islandora_find_replace_language()
{
  return [
    'pageHeader' => [
      'title' => t('Form Title'),
      'default' => t('Find objects'),
    ],
    'pageheaderdesc' => [
      'type' => 'textarea',
      'title' => t('Page Header Description'),
      'default' => t('For faster results, make your search as specific as possible. Objects must match all criteria that you select.'),
    ],
    'contentmodel' => [
      'title' => t('Content Model'),
      'default' => t('Content Model')
    ],
    'contentdesc' =>[
      'title' => t('Content Model Description'),
      'default' => t('Limit the search to objects with the selected content model.'),
    ],
    'namespace' => [
      'title' => t('Namespace'),
      'default' => t('Namespace'),
    ],
    'namespacedesc' => [
      'title' => t('Namespace description'),
      'default' => t('A single namespace to search for the string.'),
    ],
    'collection' => [
      'title' => t('Collection'),
      'default' => t('Collection'),
    ],
    'collectiondesc' => [
      'title' => t('Collection Description'),
      'default' => t('Limit the search to objects directly in the selected collection.'),
    ],
    'datastream' => [
      'title' => t('Datastream ID'),
      'default' => t('Datastream'),
    ],
    'datastreamdesc' => [
      'title' => t('Datastream ID description'),
      'default' => t('A single datastream ID (DSID) to search for the string.'),
    ],
    'search' => [
      'title' => t('Search Text'),
      'default' => t('Search text'),
    ],
    'searchdesc' => [
      'type' => 'textarea',
      'title' => t('Search Text Description'),
      'default' => t('The text to search for in the datastream. Special characters must be escaped.'),
    ],
    'replacement' => [
      'title' => t('Replacement Text'),
      'default' => t('Replacement text'),
    ],
    'replacemntdesc' => [
      'type' => 'textarea',
      'title' => t('Replacement test description'),
      'default' => t('The text to replace the search with. Special characters must be escaped. Use (empty) to replace the search text with nothing.'),
    ],
    'reg_exp_pattern' => [
      'title' => t('preg_match pattern'),
      'default' => t('Preg_match pattern'),
    ],
    'reg_exp_pattern_desc' => [
      'title' => t('preg_match pattern description'),
      'default' => t('The regular expresion to evaluate in the datastream.'),
    ],
    'reg_exp_replace' => [
      'title' => t('preg_match replacement'),
      'default' => t('Preg_match replacement'),
    ],
    'reg_exp_replace_desc' => [
      'title' => t('preg_match replacement description'),
      'default' => t('The replacement expression against your matched pattern.'),
    ],
    'selcheckbox' =>[
      'type' => 'textarea',
      'title' => t('Selectin the checkboxes below'),
      'default' => t("If selecting all checkboxes in the table below results in a warning, use this checkbox as an alternate means to 'select all'."),
    ]
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
