;
(function($)  {
  function idsimsmod_function(context)  {
    $(document).ready(function()  {
      if($(".page-node-add-ids-document").length){
	  /* if on Add IDS Document form */
	  $("#edit-field-publication-date-und-0-value-day").change(function(){
	      if($(this).val() > 1){
		  $('#edit-field-publication-date-uncertain-und-day').attr( "checked", false );
	      }
	  });
	  $("#edit-field-publication-date-und-0-value-month").change(function(){
	      if($(this).val() > 1){
		  $('#edit-field-publication-date-uncertain-und-month').attr( "checked", false );
	      }
	  });
      }
      if($(".node-ids_document-form").length){
	  /* if on Add OR Edit IDS Document form */
	  $(".field-name-field-upload-document input.form-file").change(function(){
	      /* If a Document file is uploaded set the Full Text Document URL */
	      $(this).closest('.horizontal-tabs-panes').find('.field-name-field-document-url input.form-text').val();
	  });
	  /* Licence Type Quick links - Set licence type on quick values */ 
	  $(".field-name-field-licence-type-quick-links input").change(function(){
	      //$(".field-name-field-licence-type-term input").filter('[value="'+$(this).val()+'"]').attr('checked', true);
	      $(".field-name-field-licence-type-term select").val($(this).val());
	  });
	  /* If Licence type specified directly then uncheck Quick values */
	  $(".field-name-field-licence-type-term select").change(function(){
	      if($(this).val() && $(this).val()!='_none'){
		  $(".field-name-field-licence-type-quick-links input").attr('checked', false);
	      }
	  });
      }
      /* Save node if user hits language switch tab */
      $(".page-node-edit .language-link").click(function(){
	  var redirect_after_submit_url = $(this).attr('href');
	  var form_submit_url = $("form.node-form").attr('action');
	  var temp = form_submit_url.split('node');
	  var form_submit_url_lang_neutral = '/node' + temp[1]; /* If we don't do this we get double lang code and page not found */
	  $("form.node-form").attr('action', form_submit_url_lang_neutral + '?destination=' + redirect_after_submit_url);
	  $("form.node-form").submit();
	  return false;
      });
    });
  }

  Drupal.behaviors.idsimsmod = {
    attach: function(context)  {
	idsimsmod_function(context);
    }
  }
})(jQuery);