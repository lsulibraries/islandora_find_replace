/**
 * @file
 * check if max_input_vars is met on form.
 */

maxInputVars = Drupal.settings.islandora_find_replace.maxInputVars;



(function ($) {
  $('.select-all').change(function(){
      console.log('ok');
        if($('.form-checkbox').parent().parent().parent('.selected').length >= maxInputVars){
          console.log('tooooo many');
      }
    });

  $('.form-checkbox').change(function(){
    if(this.checked) {
        if($('.form-checkbox').parent().parent().parent('.selected').length >= maxInputVars){
          console.log('tooooo many');
        }

      }

  });
}(jQuery));
