/**
 * @file
 * check if max_input_vars is met on form.
 */

maxInputVars = Drupal.settings.islandora_find_replace.maxInputVars;

(function ($) {
  $.fn.tooManySelected = function() {
    if(this.parent().parent().parent('.selected').length >= maxInputVars){
      console.log('too_many');
    }
  }

  $('.select-all').change(function(){
        $('.form-checkbox').tooManySelected();
    });

  $('.form-checkbox').change(function(){
    if(this.click) {
        $('.form-checkbox').tooManySelected();
      }

  });
}(jQuery));
