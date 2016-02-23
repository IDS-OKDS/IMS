<?php

/**
 * @file
 * Contains SearchApiAlterSiteRefFieldFilter.
 */

/**
 * Represents a data alteration that restricts entity indexes to some sites from the Site Ref taxonomy term reference field
 */
class SearchApiAlterSiteRefFieldFilter extends SearchApiAbstractAlterCallback {

	/**
	 * {@inheritdoc}
	 */
	public function supportsIndex(SearchApiIndex $index) {
		return TRUE;
	}

	/**
	 * {@inheritdoc}
	 */
	public function alterItems(array &$items) {
		if (!$this->supportsIndex($this->index) || !isset($this->options['sites'])) {
			return;
		}

		$filtered_site_tid = $this->options['sites'];

		foreach ($items as $id => $item) {
			if (isset($item->field_site_ref[LANGUAGE_NONE][0]['tid'])) {
				if ($item->field_site_ref[LANGUAGE_NONE][0]['tid'] != $filtered_site_tid) {
					unset($items[$id]);
				}
			} else {
				/* no site_ref set (shouldn't happen) */
				unset($items[$id]);
			}
		}
	}

	/**
	 * {@inheritdoc}
	 */
	public function configurationForm() {
		if ($this->supportsIndex($this->index)) {

			$sites_terms = _ids_main_get_all_site_terms();
			$sites_options_arr = array();
			foreach($sites_terms as $sites_term){
				$sites_options_arr[$sites_term->tid] = $sites_term->name;
			}

			$form['sites'] = array(
		        '#type' => 'select',
		        '#title' => t('Sites'),
		        '#default_value' => isset($this->options['sites']) ? $this->options['sites'] : array(),
		        '#options' => $sites_options_arr,
		        '#multiple' => FALSE,
			);
		}
		else {
			$form = array(
				'forbidden' => array(
					'#markup' => '<p>' . t("Items indexed by this index don't have site reference field and therefore cannot be filtered here.") . '</p>',
				),
			);
		}
		return $form;
	}

}
