<?php

function webform_signup_admin_settings() {
  $node_types = node_type_get_names();

  $form = array();
  $form['node_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Signup-enabled content types'),
    '#description' => t('Webform sign-up allows you to enable the webform components for any content type.  Choose the types on which you would like to associate webform components.'),
    '#options' => $node_types,
    '#default_value' => variable_get('webform_signup_node_types'),
  );

  $form = system_settings_form($form);
  $form['#submit'][] = 'webform_signup_admin_settings_submit';

  return $form;
}

function webform_signup_admin_settings_submit($form, &$form_state) {
  module_load_include('field.inc', 'webform_signup');
	$webform_node_types = webform_variable_get('webform_node_types');

  $webform_signup_node_types = array();
  foreach ($form_state['values']['node_types'] as $type => $value) {
    if ($value) {
      if (!in_array($type, $webform_node_types)) {
        $webform_node_types[] = $type;
			}
      $webform_signup_node_types[] = $type;
      _webform_signup_create_instance('webform_signup_date', $type);
//      _webform_signup_unhide_instance('webform_signup_date', $type);
    } else {
			_webform_signup_delete_instance('webform_signup_date', $type);
//      _webform_signup_hide_instance('webform_signup_date', $type);
		}
  }
  field_info_cache_clear();
  variable_set('webform_node_types', $webform_node_types);
  variable_set('webform_signup_node_types', $webform_signup_node_types);
}
