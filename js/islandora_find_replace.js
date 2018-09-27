/**
 * @file
 * check if max_input_vars is met on form.
 */

maxInputVars = 2;//Drupal.settings.islandora_find_replace.maxInputVars;
message = `You have selected more than the php variable max_input_vars will allow. Don't select over ${maxInputVars} items in the form!`;
markup = `<div id="console" class="clearfix"><div id="find_replace_warning" class="messages status"><h2 class="element-invisible">Status message</h2><pre>${message}</pre></div></div>`;

(function ($) {
  Drupal.behaviors.tooManyMessage = {
    attach: function (context, settings) {
      $.fn.tooManySelected = function() {
        console.log('we running');
        selected = this.parent().parent().parent('.selected').length;
        messageExists = $('#find_replace_warning').length;
        if(selected < maxInputVars){
          if (messageExists) {
            $('#find_replace_warning').parent().html('');
            console.log('replace while message exists')
          }
        }
      else {
        if(!messageExists){
          $('#content.clearfix').prepend(markup);
          console.log('prepending while message doesn"t exist');
          console.log(selected);
        }
      }
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

// Drupal.behaviors.tooManyMessage = {
//   attach: function (context, settings) {
//     alert(`You have selected more than the php variable max_input_vars will allow. Don't select over ${maxInputVars} items in the form!`);
//   }
// }

// (function ($) {
//   $.fn.tooManySelected = function() {
//     if(this.parent().parent().parent('.selected').length >= maxInputVars){
//       //Drupal.behaviors.tooManyMessage = {
//         // attach: function (context, settings) {
//           // $('input.tooManyMessage', context).once('tooManyMessage', function () {
//             alert(`You have selected more than the php variable max_input_vars will allow. Don't select over ${maxInputVars} items in the form!`);
//
//           // });
//         }
//       //}
//     }
//   }
