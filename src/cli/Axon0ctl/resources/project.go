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
	project string
)

var projectHeader = []string{
	"id",
	"",
	"creator_id",
	"created_at",
}

var createProjectCmd = &cobra.Command{
	Use:   "create PROJECT_ID",
	Short: "Create a new project.",
	Args:  cobra.ExactArgs(1),
	Run: func(cmd *cobra.Command, args []string) {
		token := Login()
		address := os.Getenv("Axon_ADDRESS")
		projectId := args[0]
		content, err := Axon_sdk.CreateProject(address, token, projectId, project, Axonctl_common.DisableTlsVerification)
		if err == nil {
			Axonctl_common.PrintSingle(content, projectHeader)
		} else {
			fmt.Println(err)
			os.Exit(1)
		}
	},
}

var getProjectCmd = &cobra.Command{
	Use:   "get PROJECT_ID",
	Short: "Get information of a specific project.",
	Args:  cobra.ExactArgs(1),
	Run: func(cmd *cobra.Command, args []string) {
		token := Login()
		address := os.Getenv("Axon_ADDRESS")
		projectId := args[0]
		content, err := Axon_sdk.GetProject(address, token, projectId, Axonctl_common.DisableTlsVerification)
		if err == nil {
			Axonctl_common.PrintSingle(content, projectHeader)
		} else {
			fmt.Println(err)
			os.Exit(1)
		}
	},
}

var listProjectCmd = &cobra.Command{
	Use:   "list",
	Short: "List all project.",
	Run: func(cmd *cobra.Command, args []string) {
		token := Login()
		address := os.Getenv("Axon_ADDRESS")
		content, err := Axon_sdk.ListProject(address, token, Axonctl_common.DisableTlsVerification)
		if err == nil {
			Axonctl_common.PrintList(content, projectHeader)
		} else {
			fmt.Println(err)
			os.Exit(1)
		}
	},
}

var deleteProjectCmd = &cobra.Command{
	Use:   "delete PROJECT_ID",
	Short: "Delete a specific project from the backend.",
	Args:  cobra.ExactArgs(1),
	Run: func(cmd *cobra.Command, args []string) {
		token := Login()
		address := os.Getenv("Axon_ADDRESS")
		projectId := args[0]
		_, err := Axon_sdk.DeleteProject(address, token, projectId, Axonctl_common.DisableTlsVerification)
		if err == nil {
			fmt.Printf("successfully deleted project '%v'\n", projectId)
		} else {
			fmt.Println(err)
			os.Exit(1)
		}
	},
}

var projectCmd = &cobra.Command{
	Use:   "project",
	Short: "Manage project.",
}

func Init_Project_Commands(rootCmd *cobra.Command) {
	rootCmd.AddCommand(projectCmd)

	projectCmd.AddCommand(createProjectCmd)
	createProjectCmd.Flags().StringVarP(&project, "", "n", "", "Project  (mandatory)")
	createProjectCmd.MarkFlagRequired("")

	projectCmd.AddCommand(getProjectCmd)

	projectCmd.AddCommand(listProjectCmd)

	projectCmd.AddCommand(deleteProjectCmd)
}
