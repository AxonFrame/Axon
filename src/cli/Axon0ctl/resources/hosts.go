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

var hostHeader = []string{
	"uuid",
	"type",
}

var listHostsCmd = &cobra.Command{
	Use:   "list",
	Short: "List all logical hosts.",
	Run: func(cmd *cobra.Command, args []string) {
		token := Login()
		address := os.Getenv("Axon_ADDRESS")
		content, err := Axon_sdk.ListHosts(address, token, Axonctl_common.DisableTlsVerification)
		if err == nil {
			Axonctl_common.PrintList(content, hostHeader)
		} else {
			fmt.Println(err)
			os.Exit(1)
		}
	},
}

var hostsCmd = &cobra.Command{
	Use:   "host",
	Short: "Manage hosts.",
}

func Init_Host_Commands(rootCmd *cobra.Command) {
	rootCmd.AddCommand(hostsCmd)

	hostsCmd.AddCommand(listHostsCmd)
}
