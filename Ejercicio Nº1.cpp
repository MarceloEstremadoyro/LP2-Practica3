#include <iostream>
#include <string>
#include <vector>
using namespace std;
namespace app {
class Proyecto {
private:
    string nombre;
public:
    Proyecto(string n) : nombre(n) {}
    string getNombre() const { return nombre; }
    void mostrar() const {
        cout << "  Proyecto: " << nombre << endl;
    }
};
class Comentario {
private:
    string texto;
public:
    Comentario(string t) : texto(t) {}
    void mostrar() const {
        cout << "  Comentario: " << texto << endl;
    }
};
class Archivo {
private:
    string nombre;
public:
    Archivo(string n) : nombre(n) {}
    void mostrar() const {
        cout << "  Archivo: " << nombre << endl;
    }
};
class Notificador {
public:
    virtual ~Notificador() {}
    virtual void notificar(const string& msg) = 0;
};
class NotificadorConsola : public Notificador {
public:
    void notificar(const string& msg) override {
        cout << "  [Consola] " << msg << endl;
    }
};
class IGestor {
public:
    virtual void mostrar() const = 0;
    virtual ~IGestor() {}
};
class GestorProyectos : public IGestor {
private:
    vector<Proyecto> proyectos;
    Notificador* notificador;
public:
    GestorProyectos(Notificador* n) : notificador(n) {}
    void agregar(const Proyecto& p) {
        proyectos.push_back(p);
        notificador->notificar("Proyecto agregado: " + p.getNombre());
    }
    void mostrar() const override {
        for (const auto& p : proyectos) p.mostrar();
    }
};
class GestorComentarios : public IGestor {
private:
    vector<Comentario> comentarios;
public:
    void agregar(const Comentario& c) {
        comentarios.push_back(c);
    }
    void mostrar() const override {
        for (const auto& c : comentarios) c.mostrar();
    }
};
class GestorArchivos : public IGestor {
private:
    vector<Archivo> archivos;
public:
    void agregar(const Archivo& a) {
        archivos.push_back(a);
    }
    void mostrar() const override {
        for (const auto& a : archivos) a.mostrar();
    }
};
class Sistema {
private:
    Notificador* notificador;
    GestorProyectos gestorProyectos;
    GestorComentarios gestorComentarios;
    GestorArchivos gestorArchivos;
public:
    Sistema()
        : notificador(new NotificadorConsola()),
          gestorProyectos(notificador) {}
    ~Sistema() { delete notificador; }
    GestorProyectos& proyectos() { return gestorProyectos; }
    GestorComentarios& comentarios() { return gestorComentarios; }
    GestorArchivos& archivos() { return gestorArchivos; }
};
}
int main() {
    cout << "Gestor de Proyectos\n";
    app::Sistema sistema;
    sistema.proyectos().agregar(app::Proyecto("Sistema en la industria 4.0"));
    sistema.proyectos().agregar(app::Proyecto("Responsabilidad universitaria FISICA"));
    sistema.comentarios().agregar(app::Comentario("Le falta completar Marco teorico"));
    sistema.comentarios().agregar(app::Comentario("Revisar los nombres de los integrantes"));
    sistema.archivos().agregar(app::Archivo("ARTICULO.pdf"));
    sistema.archivos().agregar(app::Archivo("RU FISICA.png"));
    cout << "\nProyectos:\n";
    sistema.proyectos().mostrar();
    cout << "\nComentarios:\n";
    sistema.comentarios().mostrar();
    cout << "\nArchivos:\n";
    sistema.archivos().mostrar();
    return 0;
}