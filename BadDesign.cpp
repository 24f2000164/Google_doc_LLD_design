#include<iostream>
#include<string>
#include<vector>
#include<fstream>

using namespace std;

class DocumentEditor{
    private:
        vector<string> documentElements;
        string renderDocument;
    public:
        void addtext(string text){
            documentElements.push_back(text);
        }
        void addImage(string imagePath){
            documentElements.push_back(imagePath);
        }
        string renderDocuments(){
            if (renderDocument.empty()){
            string result;
            for(auto element: documentElements){
                if(element.size()>4 && (element.substr(element.size()-4)==".jpg" || element.substr(element.size()-4)==".png")){
                    result+="[Image: " + element + "]" +"\n";
                }
                else{
                    result+=element +"\n";
                }
            }
            renderDocument=result;
           }
             
            return renderDocument;


        }


        void saveTofile(){
            ofstream file("document.txt");
            if (file.is_open()){
                file << renderDocuments();
                file.close();
                cout << "Document saved to docuement.txt" << endl;

            }
            else{
                cout << "Document Error : unabel to open the file for writing the content in it" << endl;
            }

        }



};



int main(){
    DocumentEditor editor;
    editor.addtext("Hello world this is the first design that createdd by me");
    editor.addImage("picture.jpg");
    editor.addtext("This is the document editor created by me");

    cout << editor.renderDocuments() << endl;
    editor.saveTofile();

    return 0;


}
            


