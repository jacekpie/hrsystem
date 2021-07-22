# -----------------------------
# Settings
# -----------------------------

#
USER="--user "$(id -u):$(id -g)""

#
WORK_DIR="/tmp"
PWD="-v $(pwd)/:${WORK_DIR}"

#
DOCKER_IMAGE="jacek_solution_build"

# -----------------------------
# Run docker
# -----------------------------
docker run ${USER} ${PWD} --workdir=${WORK_DIR}  ${DOCKER_IMAGE} /tmp/hrsystem $@

