# SPDX-FileCopyrightText: 2022 Daniel Aimé Valcour <fosssweeper@gmail.com>
#
# SPDX-License-Identifier: CC0-1.0

cmake_minimum_required(VERSION 3.26.1)

project(
	jman_advent_of_code
	LANGUAGES C
)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

function(aoc_year YEAR)
	set(YEAR_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${YEAR}")
	FILE(GLOB CHALLENGES RELATIVE "${YEAR_DIR}" "${YEAR_DIR}/*")
	foreach(CHALLENGE ${CHALLENGES})
		set(CHALLENGE_DIR "${YEAR_DIR}/${CHALLENGE}")
		set(TARGET_NAME "aoc_${YEAR}_${CHALLENGE}")
		add_executable("${TARGET_NAME}" "${CHALLENGE_DIR}/main.c")
		file(GLOB FILES "${CHALLENGE_DIR}/content/*")
		if (NOT FILES)
			return()
		endif()
		add_custom_command(
			TARGET "${TARGET_NAME}"
			POST_BUILD COMMAND
			${CMAKE_COMMAND} -E copy_if_different ${FILES} "$<TARGET_FILE_DIR:${TARGET_NAME}>"
		)
	endforeach()
endfunction()

aoc_year(2024)

