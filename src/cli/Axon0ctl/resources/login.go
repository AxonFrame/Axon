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
	Axonctl_common "Axonctl/common"
	"os"

	Axon_sdk "github.com/Axon0/Axon"
)

func Login() string {

	user := os.Getenv("Axon_USER")
	passphrase := os.Getenv("Axon_PASSPHRASE")
	address := os.Getenv("Axon_ADDRESS")

	if user == "" {
		panic("Axon_USER is not set")
	}
	if passphrase == "" {
		panic("Axon_PASSPHRASE is not set")
	}
	if address == "" {
		panic("Axon_ADDRESS is not set")
	}

	return Axon_sdk.RequestToken(address, user, passphrase, Axonctl_common.DisableTlsVerification)
}
