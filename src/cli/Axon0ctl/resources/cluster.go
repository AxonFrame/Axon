/**
 * @author        <.@>
 *
 * @copyright   Apache License Version 2.0
 *
 *      Copyright 2022  
 *
 *      Licensed under the Apache License, Version 2.0 (the "License");
 *      you may not use this file except in compliance with the License.
 *      You may obtain a copy of the License at
 *
 *          http://www.apache.org/licenses/LICENSE-2.0
 *
 *      Unless required by applicable law or agreed to in writing, software
 *      distributed under the License is distributed on an "AS IS" BASIS,
 *      WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *      See the License for the specific language governing permissions and
 *      limitations under the License.
 */

package Axon_resources

import (
	"fmt"
	Axonctl_common "Axonctl/common"
	"os"

	Axon_sdk "github.com/Axon0/Axon"
	"github.com/spf13/cobra"
)

var (
	templatePath   string
	checkpoint string
	checkpointUuid string
)

var clusterHeader = []string{
	"uuid",
	"",
	"visibility",
	"owner_id",
	"project_id",
	"created_at",
}

var clusterGetHeader = []string{
	"uuid",
	"",
	"visibility",
	"owner_id",
	"number_of_blocks",
	"number_of_sections",
	"project_id",
	"created_at",
}

var clusterSaveHeader = []string{
	"uuid",
	"",
}

var clusterRestoreHeader = []string{
	"uuid",
}

var createClusterCmd = &cobra.Command{
	Use:   "create -t TEMPLATE_PATH ",
	Short: "Create a new cluster.",
	Args:  cobra.ExactArgs(1),
	Run: func(cmd *cobra.Command, args []string) {
		token := Login()
		address := os.Getenv("Axon_ADDRESS")
		cluster := args[0]
		templateContent, err := os.ReadFile(templatePath)
		if err != nil {
			fmt.Println(err)
			os.Exit(1)
		}
		content, err := Axon_sdk.CreateCluster(address, token, cluster, string(templateContent), Axonctl_common.DisableTlsVerification)
		if err != nil {
			fmt.Println(err)
			os.Exit(1)
		}
		Axonctl_common.PrintSingle(content, clusterHeader)
	},
}

var getClusterCmd = &cobra.Command{
	Use:   "get CLUSTER_UUID",
	Short: "Get information of a specific cluster.",
	Args:  cobra.ExactArgs(1),
	Run: func(cmd *cobra.Command, args []string) {
		token := Login()
		address := os.Getenv("Axon_ADDRESS")
		clusterUuid := args[0]
		content, err := Axon_sdk.GetCluster(address, token, clusterUuid, Axonctl_common.DisableTlsVerification)
		if err != nil {
			fmt.Println(err)
			os.Exit(1)
		}
		Axonctl_common.PrintSingle(content, clusterGetHeader)
	},
}

var listClusterCmd = &cobra.Command{
	Use:   "list",
	Short: "List all cluster.",
	Run: func(cmd *cobra.Command, args []string) {
		token := Login()
		address := os.Getenv("Axon_ADDRESS")
		content, err := Axon_sdk.ListCluster(address, token, Axonctl_common.DisableTlsVerification)
		if err != nil {
			fmt.Println(err)
			os.Exit(1)
		}
		Axonctl_common.PrintList(content, clusterHeader)
	},
}

var deleteClusterCmd = &cobra.Command{
	Use:   "delete CLUSTER_UUID",
	Short: "Delete a specific cluster from the backend.",
	Args:  cobra.ExactArgs(1),
	Run: func(cmd *cobra.Command, args []string) {
		token := Login()
		address := os.Getenv("Axon_ADDRESS")
		clusterUuid := args[0]
		_, err := Axon_sdk.DeleteCluster(address, token, clusterUuid, Axonctl_common.DisableTlsVerification)
		if err != nil {
			fmt.Println(err)
			os.Exit(1)
		}
		fmt.Printf("successfully deleted cluster '%v'\n", clusterUuid)
	},
}

var saveClusterCmd = &cobra.Command{
	Use:   "save -n CHECKPOINT_ CLUSTER_UUID",
	Short: "Save cluster as checkpoint.",
	Args:  cobra.ExactArgs(1),
	Run: func(cmd *cobra.Command, args []string) {
		token := Login()
		address := os.Getenv("Axon_ADDRESS")
		clusterUuid := args[0]
		content, err := Axon_sdk.SaveCluster(address, token, clusterUuid, checkpoint, Axonctl_common.DisableTlsVerification)
		if err != nil {
			fmt.Println(err)
			os.Exit(1)
		}
		Axonctl_common.PrintSingle(content, clusterSaveHeader)
	},
}

var restoreClusterCmd = &cobra.Command{
	Use:   "restore -c CHECKPOINT_UUID CLUSTER_UUID",
	Short: "Restore cluster from checkpoint.",
	Args:  cobra.ExactArgs(1),
	Run: func(cmd *cobra.Command, args []string) {
		token := Login()
		address := os.Getenv("Axon_ADDRESS")
		clusterUuid := args[0]
		content, err := Axon_sdk.RestoreCluster(address, token, clusterUuid, checkpointUuid, Axonctl_common.DisableTlsVerification)
		if err != nil {
			fmt.Println(err)
			os.Exit(1)
		}
		Axonctl_common.PrintSingle(content, clusterRestoreHeader)
	},
}

var clusterCmd = &cobra.Command{
	Use:   "cluster",
	Short: "Manage cluster.",
}

func Init_Cluster_Commands(rootCmd *cobra.Command) {
	rootCmd.AddCommand(clusterCmd)

	clusterCmd.AddCommand(createClusterCmd)
	createClusterCmd.Flags().StringVarP(&templatePath, "template", "t", "", "Cluster Template (mandatory)")
	createClusterCmd.MarkFlagRequired("template")

	clusterCmd.AddCommand(getClusterCmd)

	clusterCmd.AddCommand(listClusterCmd)

	clusterCmd.AddCommand(deleteClusterCmd)

	clusterCmd.AddCommand(saveClusterCmd)
	saveClusterCmd.Flags().StringVarP(&checkpoint, "", "n", "", "Checkpoint  (mandatory)")
	saveClusterCmd.MarkFlagRequired("")

	clusterCmd.AddCommand(restoreClusterCmd)
	restoreClusterCmd.Flags().StringVarP(&checkpointUuid, "checkpoint", "c", "", "Checkpoint UUID (mandatory)")
	restoreClusterCmd.MarkFlagRequired("checkpoint")
}
