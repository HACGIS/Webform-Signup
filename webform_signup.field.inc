<?php
function _webform_signup_date_field(){
	$field = array(
		'field_name' => 'webform_signup_date',
		'type' => 'datestamp',
		'entity_types' => array('node'),
		'translatable' => true,
		'cardinality' => 1,
	);
	return $field;
}

function _webform_signup_date_instance(){
	$instance = array(
		'field_name' => 'webform_signup_date',
		'label' => t('Sign-up date'),
		'entity_type' => 'node',
	);
	return $instance;
}

function _webform_signup_create_instance($field_name, $type){
  $instance = field_info_instance('node', $field_name, $type);
  if (!$instance) {
	  $func = '_' . $field_name . '_instance';
	  $instance = $func();
	  $instance['bundle'] = $type;
	  field_create_instance($instance);
	}
}

function _webform_signup_delete_instance($field_name, $type){
  $instance = field_info_instance('node', $field_name, $type);
  if ($instance) {
	  field_delete_instance($instance, false);
	  field_purge_instance($instance);
	}
}

function _webform_signup_unhide_instance($field_name, $type){
	$options = array('include_inactive' =>  true);
	$instance = field_read_instance('node', $field_name, $type, $options);
	if ($instance) {
    $instance['active'] = true;
    field_update_instance($instance);
	} else {
		_webform_signup_create_instance($field_name, $type);
	}
}

function _webform_signup_hide_instance($field_name, $type){
  $instance = field_info_instance('node', $field_name, $type);
  if ($instance) {
    $instance['active'] = false;
    field_update_instance($instance);
	}
}
