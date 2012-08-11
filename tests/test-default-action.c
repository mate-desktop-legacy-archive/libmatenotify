/* -*- Mode: C; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 8 -*-
 *
 * @file tests/test-default-action.c Unit test: default action
 *
 * @Copyright (C) 2004 Mike Hearn <mike@navi.cx>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA  02110-1301, USA.
 */

#include <libmatenotify/notify.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define DBUS_API_SUBJECT_TO_CHANGE

#include <glib.h>
#include <dbus/dbus.h>
#include <dbus/dbus-glib.h>
#include <dbus/dbus-glib-lowlevel.h>

static GMainLoop *loop;

static void
callback (NotifyNotification *n,
          const char         *action,
          void               *user_data)
{
        printf ("callback\n");
        assert (action != NULL);
        assert (strcmp ("default", action) == 0);

        notify_notification_close (n, NULL);

        g_main_loop_quit (loop);
}

int
main ()
{
        NotifyNotification *n;
        DBusConnection     *conn;

        if (!notify_init ("Default Action Test"))
                exit (1);

        conn = dbus_bus_get (DBUS_BUS_SESSION, NULL);
        loop = g_main_loop_new (NULL, FALSE);

        dbus_connection_setup_with_g_main (conn, NULL);

        n = notify_notification_new ("Matt is online", "", NULL, NULL);
        notify_notification_set_timeout (n, NOTIFY_EXPIRES_DEFAULT);
        notify_notification_add_action (n,
                                        "default",
                                        "Do Default Action",
                                        (NotifyActionCallback) callback,
                                        NULL,
                                        NULL);
        notify_notification_set_category (n, "presence.online");

        if (!notify_notification_show (n, NULL)) {
                fprintf (stderr, "failed to send notification\n");
                return 1;
        }

        g_main_loop_run (loop);

        return 0;
}
