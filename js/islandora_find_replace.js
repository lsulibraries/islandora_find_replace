/**
 * @file
 * check if max_input_vars is met on form.
 */

maxInputVars = Drupal.settings.islandora_find_replace.maxInputVars;
message = `You have selected more than the php variable max_input_vars will allow. Don't select over ${maxInputVars} items in the form!`;
html = `<div class="messages status"><h2 class="element-invisible">Status message</h2><pre>${message}</pre></div>`;

(function ($) {
  Drupal.behaviors.tooManyMessage = {
    attach: function (context, settings) {
      $.fn.tooManySelected = function() {
        if(this.parent().parent().parent('.selected').length >= maxInputVars){
          //alert(message);
          $('#console.clearfix').val(html);
          console.log($('#console').val());
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
