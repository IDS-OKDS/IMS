<?php

/**
 * @file
 * Modifications to the the inline_entity_form widget for IDS Document URL entity objects in IDS Document nodes
 */

/*
 * Implimentation of hook_field_widget_form_alter() 
 * Used to force the first inline entity reference to be open and ready to edit 
 */

function idsims_main_field_widget_form_alter(&$element, &$form_state, $context) {
	$field = $context['field'];
	if (isset($field['field_name']) && ('field_document_urls' == $field['field_name'])) {
		if (empty($element['form']) && empty($element['entities'][0])) {
			$element['actions'] = array();
			$field = $context['field'];
			$instance = $context['instance'];
			$settings = inline_entity_form_settings($field, $instance);
			$controller = inline_entity_form_get_controller($instance);

			$parents = array_merge($element['#field_parents'], array($element['#field_name'], $element['#language']));
			$parent_langcode = entity_language($element['#entity_type'], $element['#entity']);

			$ief_id = $element['#ief_id'];

			$element['form'] = array (
		        '#type' => 'container',
		        '#op' => 'add',
		        '#parents' => array_merge($parents, array ('form')),
		        '#entity_type' => $settings['entity_type'],
		        '#parent_language' => $parent_langcode,
		        '#ief_id' => $ief_id,
			);
			$bundle = reset($settings['bundles']);

			$form_state['inline_entity_form'][$ief_id]['form settings'] = array (
        		'bundle' => $bundle,
			);

			$element['form'] = inline_entity_form_entity_form($controller, $element['form'], $form_state);
		}
	}
}

/*
 * Saving an entity translation passing in the language code the entity and array of translatable fieldname => value pairs
 */
function _idsims_main_save_entity_translation($entity_type, $entity, $langcode, $field_array){
	foreach($field_array as $field_name => $field_value_array){
		foreach($field_value_array as $delta => $field_value){
			$entity->{$field_name}[$langcode][$delta] = array(
			  'value' => $field_value,
			);	
		}
	}
	$handler = entity_translation_get_handler($entity_type, $entity);
	$translation = array(
	  'translate' => 0,
	  'status' => 1,
	  'language' => $langcode,
	  'source' => $entity->language,
	);
	$handler->setTranslation($translation, $entity);
	entity_save($entity_type, $entity);	
}


