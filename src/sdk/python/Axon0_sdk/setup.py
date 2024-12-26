from setuptools import setup
from setuptools.command.install import install
from subprocess import check_call
import os

version = os.getenv('PYTHON_PACKAGE_VERSION', '0.0.0')


class GenerateProtobufMessages(install):
    def run(self):
        # Run your custom command here
        check_call(["protoc",
                    "--python_out=./Axon_sdk",
                    "--proto_path",
                    "../../../libraries/Axon_messages/protobuffers",
                    "Axon_messages.proto3"])

        # Continue with the default installation process
        install.run(self)


setup(
    name='Axon_sdk',
    version=version,
    description='SDK library for Axon',
    url='https://github.com/AxonFrame/Axon',
    author=' ',
    author_='.@',
    license='Apache 2.0',
    packages=['Axon_sdk', 'Axon_sdk.Axon_messages'],
    install_requires=['jsonschema==4.23.0',
                      'protobuf==3.20.3',
                      'requests==2.32.3',
                      'simplejson==3.19.3',
                      'websockets==14.1'],
    cmdclass={
        'install': GenerateProtobufMessages,
    },
    classifiers=[
        'License :: Apache 2.0',
        'Operating System :: POSIX :: Linux',
        'Programming Language :: Python :: 3.9',
        'Programming Language :: Python :: 3.10',
        'Programming Language :: Python :: 3.11',
        'Programming Language :: Python :: 3.12',
    ],
)
