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
      }
    });
  }

  Drupal.behaviors.idsimsmod = {
    attach: function(context)  {
	idsimsmod_function(context);
    }
  }
})(jQuery);