;
(function($)  {
  function idsimsmod_function(context)  {
    $(document).ready(function()  {
      if($(".page-node-add-ids-document").length){
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
    });
  }

  Drupal.behaviors.idsimsmod = {
    attach: function(context)  {
	idsimsmod_function(context);
    }
  }
})(jQuery);