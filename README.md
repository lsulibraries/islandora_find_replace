# Islandora Find & Replace LSU Fork

## Introduction

An administrative user interface to perform find & replace on datastream text.

This fork has added features:

1. The php setting [max_input_vars](https://secure.php.net/manual/en/info.configuration.php#ini.max-input-vars) (which limits the number of input variables that may be accepted and helps prevent DDoS attacks), was reached when the replace.form was submitted with ~1,000+ items. We have supplied an additional checkbox outside of the results table in the replace.form. This allows the number of targets to be submitted without triggering a max_input_vars error, truncating the list of input vars and avoiding the error message. Previous behavior would refresh the replace.form page, and log an error in islandora/tools/find-replace/log. (It is entirely possible that if a user selected 1,001 items from the results table that this error could still be reproduced.)

2. The option to search for regular expressions within datastreams has been added (use with caution as it can break your metadata).

3. Allows the user to 'undo' a batch replacement from the log.inc form page for a specific batch. Clicking the 'Revert Datastream' button will set the object's datastream to the version prior to the batch replacement.

4. Allows CSV download of object pids in a given batch. This can be used in drush commands that take a CSV as input.

## Requirements

This module requires the following modules/libraries:

* [Islandora](https://github.com/islandora/islandora)
* [Tuque](https://github.com/islandora/tuque)
* [Islandora Pretty Text Diff](https://github.com/contentmath/islandora_pretty_text_diff) (optional)

## Installation

Follow the typical Drupal module installation instructions [here](https://drupal.org/documentation/install/modules-themes/modules-7).

## Documentation

Further documentation for this module is available at [www.contentmath.com](http://www.contentmath.com).

## Troubleshooting/Issues

Have an issue with the module?

* [Issue Queue](https://github.com/lsulibraries/islandora_find_replace/issues)

Need support or additional features or modifications?

* [Content Math](http://www.contentmath.com)

## Maintainers/Sponsors

Current maintainers:

* [Content Math](http://www.contentmath.com)

## License

[GPLv3](http://www.gnu.org/licenses/gpl-3.0.txt)
