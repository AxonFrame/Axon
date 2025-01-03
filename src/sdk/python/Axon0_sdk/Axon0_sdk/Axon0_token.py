# Copyright 2022  
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import requests
from . import Axon_exceptions
import base64


def request_token(address: str,
                  user_id: str,
                  passphrase: str,
                  verify_connection: bool = True) -> str:
    url = f'{address}/v1.0alpha/token'
    passphrase_bytes = passphrase.encode('utf-8')
    base64_encoded = base64.b64encode(passphrase_bytes)

    json_body = {
        "id": user_id,
        "passphrase": base64_encoded.decode('utf-8'),
    }

    response = requests.post(url, json=json_body, verify=verify_connection)
    if response.status_code == 200:
        return response.json()["token"]
    if response.status_code == 400:
        raise Axon_exceptions.BadRequestException(response.content)
    if response.status_code == 401:
        raise Axon_exceptions.UnauthorizedException(response.content)
    if response.status_code == 404:
        raise Axon_exceptions.NotFoundException(response.content)
    if response.status_code == 409:
        raise Axon_exceptions.ConflictException(response.content)
    if response.status_code == 500:
        raise Axon_exceptions.InternalServerErrorException()

# check_token
