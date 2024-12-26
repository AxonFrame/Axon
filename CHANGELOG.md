# Changelog

## v0.1.0

**Release-Date**: 2024-12-26


#### API-Breaking

- the input definition for the tasks was changes to removed the naming restriction between dataset-column and hexagon-
- the external REST-API endpoint to validate a token was removed and replaced by an internal function, which is used instead for all incoming api-requests
- changed password to passphrase, which is now required to be base64 encoded

#### Checkpoint-breaking

- added axons to be able to connect hexagons of the entire cluster with each other
- the synapse-block-links were moved into its own vector for cleaner separation and better sizes of the objects within the memory

#### Template-Breaking

- removed `target`-keyword from cluster-templates
- removed number of nodes from inputs and outputs from the cluster-templates

#### Database-Breaking

- the base64-representation of the passphrases is now used for the pw-hash inside the database, which makes all old hashes in the database invalid

### Added

- added new workaround to be able to handle binary input-data
- added new output-modi to provide more output-options to combine multiple outputs bitwise into a bigger value
- added metrics for number of blocks and number of sections to cluster get output

### Changed

- red repo from `Axon` to `Axon0`
- tls-termination in kubernetes setup was moved from the ingress into a container within the same pod like the Axon-process
- number of input- and output-neurons now scales with the given data, so defining them hard inside of the cluster-template is not longer necessary
- moved converting user-context from the endpoints to a central position to avoid unnecessary redundant code
- moved cluster io-functions internally into the processing and backpropagarion files for the cpu-code
- item-buffer was internally changed to be more compatible for further attempts of GPU-support
- made internal processing more generic, to have the same worker-workflow for all coming backends
- use debug builds with ASan-check for tests of the CI (unit-, functional-, memory-leak-, sdk-api- and cli-api-tests)
- default-values for initial admin-credentials and token-key were removed from the helm-chart and are now marked as required
- synapse-tolerance was changed to static values

### Fixed

- fixed memory-leak in DataSetFileHandle
- fixed memory violations found by the new added ASan-memory-check
- some cases of invalid http-requests had returned an 200 reponse with empty body, which was fixed
- changed token-key in helm-chart from configmap to secret
- fixed memory-corruption in cluster-resize, because a pointer was used after free
- fixed missing drawio-images in documentation when generating in CI
- fixed random crash, which can appear while creating checkpoints
- when making a request over direct-io but the output is empty, there was no response and the connection got stuck, which was fixed
- when using direct-io right from the beginning to train a cluster, the cluster remained empty, which was fixed

### Removed

- the ansible-playbook was moved ot the archive and removed from the documentation and CI

