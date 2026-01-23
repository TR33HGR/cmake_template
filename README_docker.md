## Docker Instructions

If you have [Docker](https://www.docker.com/) installed, you can run this
in your terminal, when the Dockerfile is inside the `.devcontainer` directory:

```bash
docker build -f ./.devcontainer/Dockerfile --tag=project:latest .
docker run -it project:latest
```

This command will put you in a `bash` session in a Ubuntu 20.04 Docker container,
with all of the tools listed in the [Dependencies](./README_dependencies.md#dependencies) section already installed.

You will be logged in as root, so you will see the `#` symbol as your prompt.
You will be in a directory that contains a copy of the `project`;
any changes you make to your local copy will not be updated in the Docker image
until you rebuild it.

You can configure and build as shown in the [build instructions](./README_building.md).
