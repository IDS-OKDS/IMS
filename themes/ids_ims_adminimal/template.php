<?php

/**
 * @file
 * This file contains the main theme functions hooks and overrides.
 */

/**
 * Implementation of hook_preprocess_html
 * 
 * css load order not working in info file was loading before Adminimal default
 */
function ids_ims_adminimal_preprocess_html(&$vars) {
  	// Add Override css for this sub-theme
	drupal_add_css(path_to_theme() . '/css/ids_ims_adminimal.css', array('group' => CSS_THEME, 'media' => 'all', 'weight' => 2));	
}


/**
 * Implementation of hook_preprocess_page
 */
function ids_ims_adminimal_preprocess_page(&$vars) {
	$node = (isset($vars['node'])) ? $vars['node'] : NULL;

	$lang_code = ($node) ? entity_language('node', $node) : LANGUAGE_NONE;

	$vars['lang_code'] = $lang_code;
	
	$vars['asset_id'] = '';

	if (isset($vars['node']->type) && isset($vars['node']->nid)) {
		if(isset($vars['node']->field_object_id[$lang_code][0]['value'])){
			$vars['asset_id'] = $vars['node']->field_object_id[$lang_code][0]['value'];
		}
	}
}

