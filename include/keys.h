/* Copyright (c) 2006-2014 Jonas Fonseca <jonas.fonseca@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef TIG_KEYS_H
#define TIG_KEYS_H

#include "tig.h"
#include "request.h"

/*
 * Keys
 */

struct keybinding;

struct keymap {
	const char *name;
	struct keymap *next;
	struct keybinding *data;
	size_t size;
	bool hidden;
};

void add_keymap(struct keymap *keymap);
struct keymap *get_keymap(const char *name);
struct keymap *get_keymaps(void);

const char *get_key_name(int key_value);
int get_key_value(const char *name);

/* Looks for a key binding first in the given map, then in the generic map, and
 * lastly in the default keybindings. */
enum request get_keybinding(struct keymap *keymap, int key);
void add_keybinding(struct keymap *table, enum request request, int key);

const char *get_keys(struct keymap *keymap, enum request request, bool all);
#define get_view_key(view, request) get_keys(&(view)->ops->keymap, request, FALSE)

enum run_request_flag {
	RUN_REQUEST_DEFAULT	= 0,
	RUN_REQUEST_FORCE	= 1,
	RUN_REQUEST_SILENT	= 2,
	RUN_REQUEST_CONFIRM	= 4,
	RUN_REQUEST_EXIT	= 8,
	RUN_REQUEST_INTERNAL	= 16,
};

struct run_request {
	struct keymap *keymap;
	int key;
	const char **argv;
	bool silent;
	bool confirm;
	bool exit;
	bool internal;
};

struct run_request *get_run_request(enum request request);
bool add_run_request(struct keymap *keymap, int key, const char **argv, enum run_request_flag flags);

#endif
/* vim: set ts=8 sw=8 noexpandtab: */
