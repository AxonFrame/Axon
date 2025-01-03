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
	column           string
	rowOffset            int
	numberOfRows         int
	inputFilePath        string
	labelFilePath        string
	referenceDatasetUuid string
)

var datasetHeader = []string{
	"uuid",
	"",
	"version",
	"number_of_columns",
	"number_of_rows",
	"description",
	"visibility",
	"owner_id",
	"project_id",
	"created_at",
}

var datasetCheckHeader = []string{
	"accuracy",
}

var createMnistDatasetCmd = &cobra.Command{
	Use:   "mnist -i INPUT_FILE_PATH -l LABEL_FILE_PATH DATASET_",
	Short: "Upload new mnist dataset.",
	Args:  cobra.ExactArgs(1),
	Run: func(cmd *cobra.Command, args []string) {
		token := Login()
		address := os.Getenv("Axon_ADDRESS")
		dataset := args[0]
		uuid, err := Axon_sdk.UploadMnistFiles(address, token, dataset, inputFilePath, labelFilePath, Axonctl_common.DisableTlsVerification)
		if err != nil {
			fmt.Println(err)
			os.Exit(1)
		}

		content, err := Axon_sdk.GetDataset(address, token, uuid, Axonctl_common.DisableTlsVerification)
		if err == nil {
			Axonctl_common.PrintSingle(content, datasetHeader)
		} else {
			fmt.Println(err)
			os.Exit(1)
		}
	},
}

var createCsvDatasetCmd = &cobra.Command{
	Use:   "csv -i INPUT_FILE_PATH DATASET_",
	Short: "Upload new csv dataset.",
	Args:  cobra.ExactArgs(1),
	Run: func(cmd *cobra.Command, args []string) {
		token := Login()
		address := os.Getenv("Axon_ADDRESS")
		dataset := args[0]
		uuid, err := Axon_sdk.UploadCsvFiles(address, token, dataset, inputFilePath, Axonctl_common.DisableTlsVerification)
		if err != nil {
			fmt.Println(err)
			os.Exit(1)
		}

		content, err := Axon_sdk.GetDataset(address, token, uuid, Axonctl_common.DisableTlsVerification)
		if err == nil {
			Axonctl_common.PrintSingle(content, datasetHeader)
		} else {
			fmt.Println(err)
			os.Exit(1)
		}
	},
}

var checkDatasetCmd = &cobra.Command{
	Use:   "check -r REFERENCE_DATASET_UUID DATASET_UUID",
	Short: "Check a dataset against a reference.",
	Args:  cobra.ExactArgs(1),
	Run: func(cmd *cobra.Command, args []string) {
		token := Login()
		address := os.Getenv("Axon_ADDRESS")
		datasetUuid := args[0]
		content, err := Axon_sdk.CheckDataset(address, token, datasetUuid, referenceDatasetUuid, Axonctl_common.DisableTlsVerification)
		if err == nil {
			Axonctl_common.PrintSingle(content, datasetCheckHeader)
		} else {
			fmt.Println(err)
			os.Exit(1)
		}
	},
}

var getDatasetCmd = &cobra.Command{
	Use:   "get DATASET_UUID",
	Short: "Get information of a specific dataset.",
	Args:  cobra.ExactArgs(1),
	Run: func(cmd *cobra.Command, args []string) {
		token := Login()
		address := os.Getenv("Axon_ADDRESS")
		datasetUuid := args[0]
		content, err := Axon_sdk.GetDataset(address, token, datasetUuid, Axonctl_common.DisableTlsVerification)
		if err == nil {
			Axonctl_common.PrintSingle(content, datasetHeader)
		} else {
			fmt.Println(err)
			os.Exit(1)
		}
	},
}

var listDatasetCmd = &cobra.Command{
	Use:   "list",
	Short: "List all dataset.",
	Run: func(cmd *cobra.Command, args []string) {
		token := Login()
		address := os.Getenv("Axon_ADDRESS")
		content, err := Axon_sdk.ListDataset(address, token, Axonctl_common.DisableTlsVerification)
		if err == nil {
			Axonctl_common.PrintList(content, datasetHeader)
		} else {
			fmt.Println(err)
			os.Exit(1)
		}
	},
}

var deleteDatasetCmd = &cobra.Command{
	Use:   "delete DATASET_UUID",
	Short: "Delete a specific dataset from the backend.",
	Args:  cobra.ExactArgs(1),
	Run: func(cmd *cobra.Command, args []string) {
		token := Login()
		address := os.Getenv("Axon_ADDRESS")
		datasetUuid := args[0]
		_, err := Axon_sdk.DeleteDataset(address, token, datasetUuid, Axonctl_common.DisableTlsVerification)
		if err == nil {
			fmt.Printf("successfully deleted dataset '%v'\n", datasetUuid)
		} else {
			fmt.Println(err)
			os.Exit(1)
		}
	},
}

var downloadDatasetContentCmd = &cobra.Command{
	Use:   "content -c COLUMN_ -o ROW_OFFSET -n NUMBER_OF_ROWS DATASET_UUID",
	Short: "Download content of a specific dataset.",
	Args:  cobra.ExactArgs(1),
	Run: func(cmd *cobra.Command, args []string) {
		token := Login()
		address := os.Getenv("Axon_ADDRESS")
		datasetUuid := args[0]
		content, err := Axon_sdk.DownloadDatasetContent(address, token, datasetUuid, column, numberOfRows, rowOffset, Axonctl_common.DisableTlsVerification)
		if err == nil {
			data := content["data"].([]interface{})
			Axonctl_common.PrintValueList(data, rowOffset)
		} else {
			fmt.Println(err)
			os.Exit(1)
		}
	},
}

var datasetCmd = &cobra.Command{
	Use:   "dataset",
	Short: "Manage dataset.",
}

var createDatasetCmd = &cobra.Command{
	Use:   "create",
	Short: "Upload datasets.",
}

func Init_Dataset_Commands(rootCmd *cobra.Command) {
	rootCmd.AddCommand(datasetCmd)

	datasetCmd.AddCommand(createDatasetCmd)

	createDatasetCmd.AddCommand(createMnistDatasetCmd)
	createMnistDatasetCmd.Flags().StringVarP(&inputFilePath, "input", "i", "", "Path to file with input-data (mandatory)")
	createMnistDatasetCmd.Flags().StringVarP(&labelFilePath, "label", "l", "", "Path to file with label-data (mandatory)")
	createMnistDatasetCmd.MarkFlagRequired("input")
	createMnistDatasetCmd.MarkFlagRequired("label")

	createDatasetCmd.AddCommand(createCsvDatasetCmd)
	createCsvDatasetCmd.Flags().StringVarP(&inputFilePath, "input", "i", "", "Path to file with input-data (mandatory)")
	createCsvDatasetCmd.MarkFlagRequired("input")

	datasetCmd.AddCommand(checkDatasetCmd)
	checkDatasetCmd.Flags().StringVarP(&referenceDatasetUuid, "reference", "r", "", "UUID of the dataset, which works as reference (mandatory)")
	checkDatasetCmd.MarkFlagRequired("reference")

	datasetCmd.AddCommand(downloadDatasetContentCmd)
	downloadDatasetContentCmd.Flags().StringVarP(&column, "column", "c", "", " of column to download (mandatory)")
	downloadDatasetContentCmd.Flags().IntVarP(&rowOffset, "offset", "o", 0, "Number of rows to offset (mandatory)")
	downloadDatasetContentCmd.Flags().IntVarP(&numberOfRows, "rows", "n", 1, "Number of rows to download (mandatory)")
	downloadDatasetContentCmd.MarkFlagRequired("column")
	downloadDatasetContentCmd.MarkFlagRequired("rows")

	datasetCmd.AddCommand(getDatasetCmd)

	datasetCmd.AddCommand(listDatasetCmd)

	datasetCmd.AddCommand(deleteDatasetCmd)
}
