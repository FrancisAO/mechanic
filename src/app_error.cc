/*
 * Copyright (c) 2016 the Server Mechanic Team.
 * Server Mechanic (http://server-mechanic.org)
 *
 * This file is part of Server Mechanic.
 *
 * Server Mechanic is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 */

#include "app_error.h"
#include "log.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>

/*@-formatconst@ */ void app_error_set(app_error_t* app_error, int app_errno, const char* file, const int line, const char* format, ...) {
	va_list arg_list;
	va_start(arg_list, format);
	app_error_vset(app_error, app_errno, file, line, format, arg_list);
	va_end(arg_list);
}

/*@-formatconst@ */ void app_error_vset(app_error_t* app_error, int app_errno, const char* file, const int line, const char* format, va_list arg_list) {
	int exit_code = EXIT_FAILURE;
	char cbuf[4000] = "";

	if( app_errno == APP_ERROR_MIGRATION_FAILED ) {
		exit_code = EXIT_MIGRATION_FAILED;
	}

	app_error->app_errno = app_errno;
	app_error->message[0] = (char)0; 
	app_error->exit_code = exit_code;
	app_error->file = file;
	app_error->line = line;
	if( app_errno == APP_ERROR_OK ) {
		return;
	}
	else if( app_errno == APP_ERROR_GENERIC_ERROR ) {
		(void)vsnprintf(cbuf, 4000, format, arg_list);
		(void)snprintf(app_error->message, APP_ERROR_MESSAGE_MAX_LEN, "%s (%s)", cbuf, strerror(errno));
	}
	else {
		(void)vsnprintf(app_error->message, APP_ERROR_MESSAGE_MAX_LEN, format, arg_list);
	}
}

void app_error_clear(app_error_t* app_error) {
	app_error_set(app_error, APP_ERROR_OK, "none", -1, "It's all ok.");
}

bool app_error_is_ok(app_error_t const* app_error) {
	return app_error != NULL && app_error->app_errno == APP_ERROR_OK;
}

void app_error_check(app_error_t const* app_error) {
	if( app_error_is_ok(app_error) ) {
		return;
	}

	app_error_abort(app_error);
}

void app_error_abort(app_error_t const* app_error) {
	log_error(app_error->file, app_error->line, app_error->message);
	exit(app_error->exit_code);
}

AppException::AppException(int app_errno, const char* file, const int line, const char* format, ...) {
	va_list arg_list;
	va_start(arg_list, format);
	app_error_vset(&this->app_error, app_errno, file, line, format, arg_list);
	va_end(arg_list);
}

app_error_t const* AppException::getAppError() const {
	return &this->app_error;
}