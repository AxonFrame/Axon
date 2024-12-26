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

var checkpointHeader = []string{
	"uuid",
	"",
	"visibility",
	"owner_id",
	"project_id",
	"created_at",
}

var getCheckpointCmd = &cobra.Command{
	Use:   "get CHECKPOINT_UUID",
	Short: "Get information of a specific checkpoint.",
	Args:  cobra.ExactArgs(1),
	Run: func(cmd *cobra.Command, args []string) {
		token := Login()
		address := os.Getenv("Axon_ADDRESS")
		checkpointUuid := args[0]
		content, err := Axon_sdk.GetCheckpoint(address, token, checkpointUuid, Axonctl_common.DisableTlsVerification)
		if err != nil {
			fmt.Println(err)
			os.Exit(1)
		}
		Axonctl_common.PrintSingle(content, checkpointHeader)
	},
}

var listCheckpointCmd = &cobra.Command{
	Use:   "list",
	Short: "List all checkpoint.",
	Run: func(cmd *cobra.Command, args []string) {
		token := Login()
		address := os.Getenv("Axon_ADDRESS")
		content, err := Axon_sdk.ListCheckpoint(address, token, Axonctl_common.DisableTlsVerification)
		if err != nil {
			fmt.Println(err)
			os.Exit(1)
		}
		Axonctl_common.PrintList(content, checkpointHeader)
	},
}

var deleteCheckpointCmd = &cobra.Command{
	Use:   "delete CHECKPOINT_UUID",
	Short: "Delete a specific checkpoint from the backend.",
	Args:  cobra.ExactArgs(1),
	Run: func(cmd *cobra.Command, args []string) {
		token := Login()
		address := os.Getenv("Axon_ADDRESS")
		checkpointUuid := args[0]
		_, err := Axon_sdk.DeleteCheckpoint(address, token, checkpointUuid, Axonctl_common.DisableTlsVerification)
		if err != nil {
			fmt.Println(err)
			os.Exit(1)
		}
		fmt.Printf("successfully deleted checkpoint '%v'\n", checkpointUuid)
	},
}

var checkpointCmd = &cobra.Command{
	Use:   "checkpoint",
	Short: "Manage checkpoint.",
}

func Init_Checkpoint_Commands(rootCmd *cobra.Command) {
	rootCmd.AddCommand(checkpointCmd)

	checkpointCmd.AddCommand(getCheckpointCmd)

	checkpointCmd.AddCommand(listCheckpointCmd)

	checkpointCmd.AddCommand(deleteCheckpointCmd)
}
