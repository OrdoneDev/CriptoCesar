#include <gtk/gtk.h>
#include <string>
#include <cstring>
#include <iomanip>
using namespace std;

const char Alfabeto[26]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'}; 

GtkWidget *entry_text, *entry_deslocamento;

char Encrypt(char letra){
	short x = 0, y = 0;
	y = atoi(gtk_entry_get_text(GTK_ENTRY(entry_deslocamento)));
	for (short j = 0; j < 26; ++j){
		if (Alfabeto[j] == toupper(letra)){
			x = (j + y) % 26;
			return Alfabeto[x];
		}
	}
}

char Decrypt(char letra){
	short x = 0, y = 0;
	y = atoi(gtk_entry_get_text(GTK_ENTRY(entry_deslocamento)));
	for (short j = 0; j < 26; ++j){
		if (Alfabeto[j] == toupper(letra)){
			x = (j - y) % 26;
			if (x < 0){
				x = 26 + x;
			}
			return Alfabeto[x];
		}
	}
}

static void Crypt_click(GtkWidget *widget, gpointer data){
	string mensagem, criptograph = "Resultado: ";
	mensagem = gtk_entry_get_text(GTK_ENTRY(entry_text));
	for (int i = 0; i < mensagem.size(); ++i){
		if (mensagem[i] == ' '){
			criptograph += ' ';
			continue;
		}
		criptograph += Encrypt(mensagem[i]);
	}
	gtk_label_set_text(GTK_LABEL(data), criptograph.c_str());
}

static void Decrypt_click(GtkWidget *widget, gpointer data){
	string mensagem, criptograph = "Resultado: ";
	mensagem = gtk_entry_get_text(GTK_ENTRY(entry_text));
	for (int i =0; i < mensagem.size(); ++i){
		if (mensagem[i] == ' '){
			criptograph += ' ';
			continue;
		}
		criptograph += Decrypt(mensagem[i]);
	}
	gtk_label_set_text(GTK_LABEL(data), criptograph.c_str());
}

int main(int argc, char *argv[]){
	gtk_init(&argc, &argv);

	GtkWidget *janela, *lbl_title, *lbl_result, *lbl_title_deslocamento, *btn_cript, *btn_decript, *vbox1, *vbox2, *vbox3, *hbox_principal;

	janela=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	lbl_title=gtk_label_new("Texto:");
	lbl_result=gtk_label_new("Resultado: ");
	lbl_title_deslocamento=gtk_label_new("Quantidade de vezes a deslocar:");
	btn_cript=gtk_button_new_with_mnemonic("_Criptografar");
	btn_decript=gtk_button_new_with_mnemonic("_Descriptografar");
	entry_text=gtk_entry_new();
	entry_deslocamento=gtk_entry_new();
	vbox1=gtk_vbox_new(0,0);
	vbox2=gtk_vbox_new(0,0);
	vbox3=gtk_vbox_new(0,0);
	hbox_principal=gtk_hbox_new(0,0);

	gtk_box_pack_start(GTK_BOX(vbox1), lbl_title,0,0,10);
	gtk_box_pack_start(GTK_BOX(vbox1), lbl_title_deslocamento,0,0,10);

	gtk_box_pack_start(GTK_BOX(vbox2), entry_text,0,1,0);
	gtk_box_pack_start(GTK_BOX(vbox2), entry_deslocamento,0,1,0);
	gtk_box_pack_start(GTK_BOX(vbox2), lbl_result,0,0,0);

	gtk_box_pack_start(GTK_BOX(vbox3), btn_cript, 0,0,0);
	gtk_box_pack_start(GTK_BOX(vbox3), btn_decript, 0,0,0);

	gtk_box_pack_start(GTK_BOX(hbox_principal), vbox1,0,0,0);
	gtk_box_pack_start(GTK_BOX(hbox_principal), vbox2,1,1,0);
	gtk_box_pack_start(GTK_BOX(hbox_principal), vbox3,0,0,0);

	g_signal_connect(janela, "delete_event", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(btn_cript, "clicked", G_CALLBACK(Crypt_click), (gpointer)lbl_result);
	g_signal_connect(btn_decript, "clicked", G_CALLBACK(Decrypt_click), (gpointer)lbl_result);

	gtk_container_add(GTK_CONTAINER(janela), hbox_principal);
	gtk_window_set_title(GTK_WINDOW(janela), "Criptografia de Cesar");

	gtk_widget_show_all(janela);
	gtk_main();
	return 0;
}
