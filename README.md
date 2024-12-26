# Axon


![Platform](https://img.shields.io/badge/Platform-Linux-blue?style=flat-square)
![Architecture](https://img.shields.io/badge/Architecture-amd64%20%2B%20arm64-blue?style=flat-square)
![Open-Source](https://img.shields.io/badge/Open-Source-green?style=flat-square)
[Twitter / X](https://x.com/Axon_OS)
[Documentation](https://axon-4.gitbook.io/axon)
[Website](https://axon0.com/)



<p align="center">
  <img src="assets/banner.png"/>
</p>



## About Axon

Axon is an artificial neural network with a transformational impact on agent deployment. It is based on the replication of partial brain functionality through artificial neural networks. 
With the help of a stable network infrastructure, the agent technology Axon introduces will eliminate technical barriers between machine agents and facilitate the evolution of the network. 
Unlike standard neural networks, it uses real-time input data that are not filtered or standardized, such as market indicators or transaction data. 
The network is algorithmic, thus not only can Axon replace, but also add neurons and synapses while learning.

Axon redefines the landscape for intelligent systems by providing an interconnected infrastructure for agent deployment and collaboration. 
Its ability to scale, learn, and adapt makes it a powerful tool for developers looking to harness advanced neural network technology for enhanced decision-making and automation.


## Key Characteristics

-   **Growing neural network**:

	Axon’s ability to dynamically expand its architecture allows it to scale with evolving datasets, enabling the rapid deployment of adaptive agents and fostering a decentralized ecosystem where newly launched agents interconnect and enhance one another.

-   **No Input Normalization Required**

    By processing raw data without the need for normalization, 
    Axon handles real-world inputs such as live market feeds, transaction histories, and token performance metrics with ease.

-   **Agent Interconnectivity**

    The processing structure works also for multiple threads, which can work at the same time on the same network. (GPU-support with CUDA is disabled at the moment for various reasons).

-   **No Strict Layer Structure**

    The foundation of a new neural network is established through a cluster template. These templates define the network's structure using hexagons instead of layers. When a node attempts to create a new synapse, the target node's location is determined by the position of the source node within these hexagons. The target is chosen randomly, with the probability influenced by the distance from the source. This approach allows the network to deviate from a fixed layer structure. However, by arranging hexagons in a linear fashion and permitting nodes to connect only to nodes in the next hexagon, a traditional layer structure can still be implemented.

    Refer to the brief explanation and measurement examples for more insights.

-   **Reduction Process:**

    The concept of a growing network implies that there is virtually no limit to its size, even if the growth rate decreases over time. To further restrict this growth rate, a reduction process can be implemented. This process removes synapses that remain too inactive to reach the threshold for being marked as persistent.

    Refer to measurement examples for details.

-   **Neural Network Spiking**

    This concept also accommodates an optional functionality for operating as a spiking neural network. In this mode, an input's effect is influenced by previous inputs, depending on the time elapsed since those inputs occurred.

-   **Generated OpenAPI-Documentation**

    The OpenAPI documentation is automatically generated from the code. Any updates to an endpoint's configuration in the code are instantly reflected in the documentation, ensuring synchronization between the codebase and its corresponding documentation.

    Refer to the OpenAPI documentation for more details.

-   **3-D Networks**

    It is also possible to define 3D networks. This feature was introduced as a parallel to the human brain's 3D structure. Although included in the cluster templates, this capability has not yet been tested extensively. It may become beneficial in larger tests, enabling better mixing of information.

-   **Multi-user and multi-project**

    The project supports multiple users and projects with different roles, including member, project admin, and admin. Access to individual API endpoints is managed through a policy file. Users can log in with a user and passphrase to receive a JWT token, granting access to user- and project-specific resources.

    Refer to the authentication documentation for additional details.


-   **Efficient resource-usage**

    The network design ensures that only the active nodes' necessary synapses are processed based on the input. As a result, minimal processing time is required when only a small number of input nodes receive data.

    The multi-user feature allows multiple users' networks to run on the same physical host, sharing resources like RAM, CPU cores, and even the GPU without needing virtual machines or vCPUs. Additionally, there is functionality to regulate CPU frequency and measure power consumption, though this is currently disabled.

    Refer to the monitoring documentation for further information.

-   **Network-input**

    There are two methods for interacting with neural networks:

        Upload a dataset and initiate an asynchronous task using the dataset through the API. Refer to the OpenAPI documentation for details.

        Interact directly with the neural network via a websocket. In this mode, only a single input is sent through the synapse instead of an entire dataset. The call remains blocking until the network returns an output, allowing for greater control.

        Refer to the websocket documentation for more details.
-   **Installation on Kubernetes and with Ansible**

    The backend can be basically deployed on kubernetes via Helm-chart or plain via Ansible.



## Getting started

-   [Example-Workflow](https://axon-4.gitbook.io/axon/frontend)

-   [Installation-Guide](https://axon-4.gitbook.io/axon/backend/installation)

-   [SDK and CLI documentation](https://axon-4.gitbook.io/axon/frontend/cli-sdk-docu)

## Development

-   [How to build](https://axon-4.gitbook.io/axon/development/how-to-build)

-   [Development-Guide](https://axon-4.gitbook.io/axon/development/development)

-   [Dependency-Overview](https://axon-4.gitbook.io/axon/development/dependencies)
