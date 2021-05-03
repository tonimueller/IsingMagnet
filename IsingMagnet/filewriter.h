#ifndef FILEWRITER_H
#define FILEWRITER_H
#include <string>
#include <fstream>
class FileWriter{
public:
    //! constructor 
    FileWriter(std::string filename_=""):filename(filename_){}
    //! set the filename 
    void setFilename(std::string filename_){filename=filename_;}
    //! get the filename 
    std::string const getFilename(){return filename;}
    //!write data 
    template <class T >
    bool writeData(std::vector<std::vector<T> > data,std::string header=""){
        std::ofstream out(filename,std::ofstream::trunc);
        if( !out.good()) return false; 
        out << "#"<< header; 
        for (auto j=0 ; j < data[0].size();j++){
            for (auto i=0 ; i < data.size();i++)
                out << data[i][j] << "\t";
            out << "\n";
        }
        out.close();
    }
private:
    //!filename 
    std::string filename;
};
#endif /*FILEWRITER_H*/