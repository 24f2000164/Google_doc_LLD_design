#include<iostream>
#include<vector>
#include<string>
#include<fstream>
using namespace std;

class DocumentElement{
public:
  virtual string render()=0;

};

class TextElement : public DocumentElement{
private:
string text;
public:
  TextElement(string text){
    this->text=text;
  }

  string render() override{
    return text;
  }
  
};


class ImageElement : public DocumentElement{
private:
  string imagepath;
public:
  ImageElement(string imagepath){
    this->imagepath=imagepath;
  }
  string render(){
    return "[image: "+imagepath + "]";
  }
};



class NewlineElement :public DocumentElement{
 
public:
    string render() override{
        return "\n";

    }
};

class TapspaceElement : public DocumentElement{
public:
   string render(){
    return "\t";
   }
};


class Document{
 
private:
  vector<DocumentElement*> documentElements;
public:
  void addElement(DocumentElement* element){
    documentElements.push_back(element);



  }
  string render(){
    string result;
    for(auto element: documentElements){
        result+=element->render();

    }
    return result;
  }
  
};



class Persistance{
public:
  virtual void save(string data)=0;

};
class FileStorage: public Persistance{
public:
   void save(string data) override{
    ofstream outFile("document02.txt");
    if(outFile){
        outFile << data;
        outFile.close();
        cout << " Document saved successfully into the docuement2.txt" << endl;


    }
    else{
        cout << "Error: Unable to open the file to write the content" << endl;
    }

  }

};


class DBStorage: public Persistance{
public:
  void save(string data) override{
    // connect with the db;

  }
};


class DocumentEditor{
private:
  Document* document;
  Persistance* storage;
  string renderDocument;
public:
  DocumentEditor(Document* document, Persistance* storage){
    this->document=document;
    this->storage=storage;
  }

  void addText(string text){
    document->addElement(new TextElement(text));
  }
  void addImage(string imagepath){
    document->addElement(new ImageElement(imagepath));
  }

  void addNewline(){
    document->addElement(new NewlineElement());
  }

  void addtabspace(){
    document->addElement(new TapspaceElement());
  }

  string renderdocument(){
    if(renderDocument.empty()){
        renderDocument=document->render();
    }
    return renderDocument;
  }

  void saveDocument(){
    storage->save(renderdocument());
  }
  
};





int main(){
    Document* document=new Document();
    Persistance* persistance=new FileStorage();
    DocumentEditor* editor=new DocumentEditor(document, persistance);


    editor->addText("Hello world , this is the good design doc");
    editor->addNewline();
    editor->addImage("kocker.png");
    editor->addNewline();
    editor->addtabspace();
    editor->addText("Indented text after a tab space");


    cout << editor->renderdocument()  << endl;
    editor->saveDocument();
    return 0;
}
