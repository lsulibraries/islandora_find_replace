/**
 * @file
 * check if max_input_vars is met on form.
 */

maxInputVars = Drupal.settings.islandora_find_replace.maxInputVars;
message = `You have selected more than the php variable max_input_vars will allow. Don't select over ${maxInputVars} items in the form!`;
markup = `<div id="console" class="clearfix"><div id="#find_replace_warning" class="messages status"><h2 class="element-invisible">Status message</h2><pre>${message}</pre></div></div>`;

(function ($) {
  Drupal.behaviors.tooManyMessage = {
    attach: function (context, settings) {
      $.fn.tooManySelected = function() {
        selected = this.parent().parent().parent('.selected').length;
        if (selected >= maxInputVars) {
          if ($('#find_replace_warning').length) {
            console.log('replace');
            $('#find_replace_warning').html('');
          }
          else {
            console.log('prepend');
            $('#content.clearfix').prepend(markup);
          }
          console.log(selected);
        }
        else {
          console.log('not_greater_than');
          $('#console.clearfix').html('');
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
