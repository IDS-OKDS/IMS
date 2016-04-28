<?php

/**
 * @file
 * Get and process data from the Full Document URL
 */

/*
 * Lookup the Full Document URL and save additional information to the entity:
 * Mime Type
 * Cover Image
 */
function _idsims_main_save_full_document_url_info(&$entity){
	$field_language = _idsims_main_field_language('ids_document_url', $entity, 'field_document_url');
	if(isset($entity->field_document_url[$field_language])){
		$full_url = $entity->field_document_url[$field_language][0]['value'];
		if($full_url){
			/* If file upload then property set full document URL */

			/* set mime type field */
			$mime_type = _idsims_main_get_url_mime_type($full_url);
			if($mime_type){
				$terms = taxonomy_get_term_by_name($mime_type, $vocabulary = 'ids_mime_type');
				if(!count($terms)){
					$vid = _idsims_main_get_vid_from_vocab_machine_name('ids_mime_type');
					$tid = _idsims_main_create_taxonomy_term($mime_type, $vid);
					$term = new stdClass();
					$term->tid = $tid;
					$terms = array();
					$terms[$tid] = $term;
				}
				foreach($terms as $term){
					$tid = $term->tid;
					_idsims_main_apply_term_to_entity_field($entity, 'mime_type', $tid);
				}
				if($mime_type == 'application/pdf'){
					/*if cover image not already present (or overwritten) */
					if(!isset($entity->field_cover_image[$field_language][0]['fid'])){
						/* create and set cover image field */
						$thumbnail_file_obj = _idsims_main_thumb_pdf($full_url);
						if($thumbnail_file_obj){
							if(isset($thumbnail_file_obj->fid)){
								_idsims_main_update_entity_field($entity, 'field_cover_image', $thumbnail_file_obj->fid, $delta = 0, $store_id = 'fid');
							}
						}
					}
				}
			}
		}
	}
}

/*
 * Create image file from remote PDF
 */
function _idsims_main_thumb_pdf($pdf, $width = 300) {
	drupal_set_message($pdf);
	//if(!variable_get('idsims_import_batch_process_running', 0) ||
	//(variable_get('idsims_import_do_set_cover_thumb_image', 0) && variable_get('idsims_import_batch_process_running', 0)) ){
		try {
			$files_directory_path = variable_get('file_public_path', conf_path() . '/files');
			$storageprefix = "public://";
			$coverthumbs_dir = 'coverthumbs';
			$coverthumbs_dir_full_path = $files_directory_path . '/' . $coverthumbs_dir;
			if( is_dir($coverthumbs_dir_full_path) === false ){
				mkdir($coverthumbs_dir_full_path);
			}
			$format = "png";
			$source = $pdf;
			$sanitized_filename = _idsims_main_sanitize_file_name($pdf);
			$temp_img_dest = "$coverthumbs_dir_full_path/" . $sanitized_filename . '-temp' . ".$format";
			$final_img_dest = $storageprefix . $coverthumbs_dir . '/' . $sanitized_filename . ".$format";
			//if (!file_exists($final_img_dest)) /* Dont need to check this anymore as we check if the field has content */
			//{
			/* We have to download the PDF else we couldn't get the cover page
			* (it always got the last page from remote URL even though specified [0]?)
			*/
			$pdf_dest = "$coverthumbs_dir_full_path/" . $sanitized_filename;
			/* Here we download the pdf and save it locally */
			$pdf_file = file_get_contents($source);
			$fp  = fopen($pdf_dest, 'w+') or die('Could not create the file');
			fputs($fp, $pdf_file) or die('Could not write to the file');
			fclose($fp);
			unset($pdf_file);
			/* Now create the cover image file */
			$imagick = new Imagick($pdf_dest . '[0]');
			$imagick->setImageFormat($format);
			$imagick->scaleImage($width, 0);
			/* Set white background if transparent */
			if($imagick->getImageAlphaChannel()){
				$imagick->setImageBackgroundColor('white');
				$imagick->setImageAlphaChannel(11);
				$imagick->mergeImageLayers(Imagick::LAYERMETHOD_FLATTEN);
			}
			$imagick->writeImage($temp_img_dest);
			drupal_set_message('Cover thumbnail image created');
			/* Now delete PDF file as we might not have hosting rights */
			unlink($pdf_dest);
			/* Now save the file in the way drupal likes it! i.e. save to DB */
			$image = file_get_contents($temp_img_dest, FILE_USE_INCLUDE_PATH); // string

			$file = file_save_data($image, $final_img_dest, FILE_EXISTS_REPLACE);
			/* Now delete temp image */
			unlink($temp_img_dest);
			return $file;
			//}
		}
		catch(Exception $e) {
			echo $e->getMessage();
		}
	//}
	return FALSE;
}


/*
 * Create references to Document Abstracts on Document URL nodes
 */
function _idsims_main_update_references_to_document_abstracts(&$entity, $type, $asset_id){
	/*
	 * Make references in IDS Document URL Entities to IDS Document nodes
	 * Add IDS Document node Asset ID (object_id) as Asset ID (object_id) in entity
	 *
	 * First find the IDS Document URL Entities attached to this node
	 */
	$field_language = _idsims_main_field_language($type, $entity, 'field_document_urls');
	if(isset($entity->field_document_urls[$field_language])){
		$document_url_entity_ids = array();
		foreach($entity->field_document_urls[$field_language] as $key => $item){
			$document_url_entity_ids[] = $item['target_id'];
		}
		if(count($document_url_entity_ids)){
			$document_url_entities = entity_load('ids_document_url', $document_url_entity_ids);
			foreach($document_url_entities as $key => $document_url_entity){
				_idsims_main_update_entity_field($document_url_entity, 'field_object_id', $asset_id);
				field_attach_update('ids_document_url', $document_url_entity);
			}
		}
	}
}