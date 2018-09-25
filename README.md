# Islandora Find & Replace LSU Fork

## Introduction

An administrative user interface to perform find & replace on datastream text.

This fork has added features:

1. Previously the table-select on the replace form didn't support submissions that exceeded the php setting max_input_vars. We have supplied an additional checkbox outside of the table-select which allows all targets to be submitted without hitting this limit.

2. Adds the option to use a regular expressions to search.

3. Allows a batch to be revert datastreams to the version prior to the batch replacement.

4. Allows csv download of object pids in a given batch. This can be used in drush commands that take a CSV as input.

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

* [Issue Queue](https://github.com/contentmath/islandora_find_replace/issues)

Need support or additional features or modifications?

* [Content Math](http://www.contentmath.com)

## Maintainers/Sponsors

Current maintainers:

* [Mitch MacKenzie](http://www.contentmath.com)

## License

[GPLv3](http://www.gnu.org/licenses/gpl-3.0.txt)
