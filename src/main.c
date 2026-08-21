#include <gtk/gtk.h>
#include <webkit/webkit.h>

#define APP_ID "com.github.kindleweb.Kindle"
#define KINDLE_URL "https://read.amazon.com/"

static char *
get_data_dir(void)
{
    const char *dir = g_get_user_data_dir();
    return g_build_filename(dir, APP_ID, NULL);
}

static void
load_failed(WebKitWebView *web_view,
            WebKitLoadEvent event,
            const char *failing_uri,
            GError *error,
            gpointer user_data)
{
    (void)web_view;
    (void)event;
    (void)user_data;

    g_warning("Failed to load %s: %s",
              failing_uri ? failing_uri : "(unknown)",
              error ? error->message : "(unknown error)");
}

static void
activate(GtkApplication *app, gpointer user_data)
{
    (void)user_data;

    GtkWidget *window;
    WebKitWebView *web_view;
    WebKitNetworkSession *session;
    WebKitCookieManager *cookies;
    char *data_dir;
    char *cookies_path;

    window = gtk_application_window_new(app);

    gtk_window_set_title(GTK_WINDOW(window), "Kindle");
    gtk_window_set_default_size(GTK_WINDOW(window), 1280, 850);

    data_dir = get_data_dir();
    cookies_path = g_build_filename(data_dir, "cookies.txt", NULL);
    g_mkdir_with_parents(data_dir, 0700);

    session = webkit_network_session_new(data_dir, data_dir);
    g_free(data_dir);

    webkit_network_session_set_persistent_credential_storage_enabled(
        session, TRUE);

    cookies = webkit_network_session_get_cookie_manager(session);
    webkit_cookie_manager_set_persistent_storage(
        cookies,
        cookies_path,
        WEBKIT_COOKIE_PERSISTENT_STORAGE_TEXT);
    g_free(cookies_path);

    web_view = WEBKIT_WEB_VIEW(
        g_object_new(WEBKIT_TYPE_WEB_VIEW,
                     "network-session", session,
                     NULL)
    );
    g_object_unref(session);

    g_signal_connect(
        web_view,
        "load-failed",
        G_CALLBACK(load_failed),
        NULL
    );

    gtk_window_set_child(
        GTK_WINDOW(window),
        GTK_WIDGET(web_view)
    );

    webkit_web_view_load_uri(
        web_view,
        KINDLE_URL
    );

    gtk_window_present(GTK_WINDOW(window));
}

int
main(int argc, char **argv)
{
    GtkApplication *app;

    app = gtk_application_new(
        APP_ID,
        G_APPLICATION_DEFAULT_FLAGS
    );

    g_signal_connect(
        app,
        "activate",
        G_CALLBACK(activate),
        NULL
    );

    int status = g_application_run(
        G_APPLICATION(app),
        argc,
        argv
    );

    g_object_unref(app);

    return status;
}


