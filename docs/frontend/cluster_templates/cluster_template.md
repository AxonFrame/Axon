# Cluster Templates

## General

The cluster-templates are used to define the basic structure of a network. This defined structure is
comparable to a plant trellis. It is basically structures in hexagons, which are called hexagons.

![step1](cluster_template_general.drawio)

General structure of the file:

```
version: 1
settings:
    neuron_cooldown: <COOL_DOWN>
    refractory_time: <REFRACTORY_TIME>
    max_connection_distance: <MAX_DISTANCE>
    enable_reduction: <ENABLE_REDUCTION>

hexagons:
    X,Y,Z
    X,Y,Z
    ...
    X,Y,Z

axons:
    X,Y,Z -> X,Y,Z

inputs:
    <>: X,Y,Z
    <>: X,Y,Z (binary)

outputs:
    <>: X,Y,Z
    <>: X,Y,Z (float)
```

In the template the position, type and  of the hexagons has to be defined. The size of the input
and output is defined by the given data when starting a training.

### version

At the moment this is only a placeholder an the `version: 1` is the only supported value at the
moment. There are still too much changes to handle multiple versions currently.

### settings

The entries within this block are all optional. If not listed, the default is used.

-   **neuron_cooldown**

    It the value of how much the potential of a neuron is reduced from one cycle to the next. As
    default it is so high, that the remaining potential has no impact on the next cycle anymore.

-   **refractory_time**

    Gives the number of cycles until a triggered neuron can be triggered again by the input. Within
    this time-perios, only the cooldown of the neuron is active. (Default = 1; Minimum = 1)

-   **max_connection_distance**

    Maximum distance in number-of-hexagon, which a synapses can reach from the source- to the
    target-neuron. (Default = 1; Minimum = 1)

-   **enable_reduction**

    Enable reduction-process to cleanup network. (Defaul: false)

### position

`X,Y,Z` the x-, y- and z-coordinates of the hexagon. All hexagons must be connected by at
least one side with another hexagon.

!!! info

    It is theoretically possible to order them 3-dimensional by using different z-values, but this was never tested until now.

### target

Inputs and outputs is also a `X,Y,Z` and has to be the same position, like the hexagon, where
this input or output should be connected to.

### 

`<>` of this input and output for identification to be able to add input- and output-values.

### binary input (optional setting)

For the case that the input-data have only value 0 and 1, a `(binary)` has to be added at the end of the input:

```
inputs:
    <>: X,Y,Z (binary)
```

Otherwise the results for binary input become really bad. Even the input on the hexagon with this flag is not a binary input, all input-values greater than 0 are automatically handled as 1. 

### axons (optional setting)

The `axons`-section is not required and allow to connect any hexagon within the cluster with another one. 

### output-type (optional setting)

Use the `(bool)`, `(float)` or `(int)` to modify the output.

```
outputs:
    <>: X,Y,Z (bool)
    <>: X,Y,Z (float)
    <>: X,Y,Z (int)
```

- `(bool)`: outputs can only have value 0 or 1 and nothing between
- `(float`: 32 outputs internally are combined bitwise to a float-value
- `(int)`: 64 outputs internally are combined bitwise to a uin64-value

!!! info

    `(bool)` and `(int)` are still converted to a float at the end, before writing into a dataset-file. Will be chanded in the future.

## Simple example

The following is a minimal example for a cluster-template.

```
version: 1
settings:
    neuron_cooldown: 100000000000.0
    refractory_time: 1
    max_connection_distance: 1
    enable_reduction: false

hexagons:
    1,1,1
    3,1,1
    4,1,1

axons:
    1,1,1 -> 3,1,1

inputs:
    input_hexagon: 1,1,1

outputs:
    output_hexagon: 4,1,1
```

It defines 3 hexagons. It contains an input-hexagon with the  `test_input` and an output-hexagon
with  `test_output`. Based on their position, they are all in a straight line, like in the image
below:

![step1](cluster_template_example.drawio)
