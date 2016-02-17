(function ($, Drupal, window, document, undefined) {

    Drupal.behaviors.ids_ims_admin = {
        attach: function (context, settings) {

            $(window).ready(function () {
                // Execute code once the window is ready.
        	$('.view-site-toggle #edit-user-1-field-selected-site-und').change(function(){
        	    $('#editableviews-entity-form-site-toggle').submit();
        	});
        	/* Add help to labels on forms */
        	$('div.form-wrapper').each(function(){
                    var label_obj = $(this).find('label').first();
                    var description_obj = $(this).find('.description').first();
        	    if(description_obj){
        		var description_html = description_obj.html();
        		if(description_html){
        		    alert(description_html);
                		label_obj.attr('title', description_html);
                		label_obj.addClass('helpTip');
                		label_obj.find('.help').first().remove();
                		label_obj.append('<span class="help">?</span>');
        	    	}
        	    }
        	});
            });

            $(window).load(function () {

            });

            $(window).resize(function () {
                // Execute code when the window is resized.
            });

            $(window).scroll(function () {
                // Execute code when the window scrolls.
            });

            $(document).ready(function () {
                // Execute code once the DOM is ready.
                // Execute code once the window is fully loaded.
                var href = window.location.href;
                var href_arr = href.split('#');
                if (href_arr[1] != undefined) {
                    var popupquery = href_arr[1];
                    var popupquery_arr = popupquery.split('&');
                    for (var query_item_raw in popupquery_arr) {
                        var query_item = popupquery_arr[query_item_raw].split('=');
                        if (query_item[1] != undefined) {
                            var value_for_form = unescape(query_item[1]);
                            if (query_item[0] == 'title') {
                                $('#edit-title').val(value_for_form);
                            }
                            if (query_item[0] == 'url') {
                                $('#edit-field-external-urls-und-0-value').val(value_for_form);
                                $('#edit-field-document-urls-und-form-field-document-url-und-0-value').val(value_for_form);
                            }
                            if (query_item[0] == 'description') {
                                $('#edit-body-und-0-value').val(value_for_form);
                            }
                        }
                    }
                }
            });
        }
    };


})(jQuery, Drupal, this, this.document);
