#include<gtk/gtk.h>

# Compile
# gcc -o best best.c `pkg-config --libs --cflags gtk+-2.0`

int main(int argc,char **argv)
{
    GtkWidget *dialog;
    
    gtk_init(&argc, &argv);
    
    dialog = gtk_message_dialog_new_with_markup(NULL, 0,GTK_MESSAGE_INFO,GTK_BUTTONS_CLOSE, "<span size='xx-large' weight='bold'>Arch is the best!</span>");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}
