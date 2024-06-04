#include "Framework.h"

string Utility::ToString(wstring value)
{
    string temp;
    temp.assign(value.begin(), value.end());

    return temp;
}

wstring Utility::ToWString(string value)
{
    wstring temp;
    temp.assign(value.begin(), value.end());

    return temp;
}

void Utility::Replace(OUT string& str, IN const string& comp,IN  const string& rep)
{
    size_t at = 0;  // 여기서 부터 찾는다.
    //해당 문자가 comp에 있으면 진행
    while ((at = str.find(comp, at)) != string::npos)
    {
        str.replace(at, comp.length(), rep);
        at += rep.length();
    }
}

vector<string> Utility::SplitString(string origin, const string& tok,const bool& includeLast)
{
    vector<string> result;

    size_t cutAt = 0;
    while ((cutAt = origin.find_first_of(tok)) != origin.npos)
    {
        if (cutAt > 0)
            result.push_back(origin.substr(0, cutAt));

        origin = origin.substr(cutAt + 1);
    }

    if (includeLast && origin.length() > 0)
        result.push_back(origin);

    return result;
}

wstring Utility::GetExtension(wstring path)
{
    size_t index = path.find_last_of('.');

    return path.substr(index + 1, path.length());
}

string Utility::GetFileName(string path)
{
    Replace(path, "\\", "/");
    size_t index = path.find_last_of('/');

    return path.substr(index + 1);
}

string Utility::GetFileNameWithoutExtension(string path)
{
    string fileName = GetFileName(path);
    size_t  index = fileName.find_last_of('.');

    return fileName.substr(0,index);
}

bool Utility::ExistDirectory(string path)
{
    DWORD fileValue = GetFileAttributesA(path.c_str());

    BOOL temp = (fileValue != INVALID_FILE_ATTRIBUTES && (fileValue & FILE_ATTRIBUTE_DIRECTORY));
    return temp == TRUE;
}

bool Utility::ExistFile(string path)
{
    DWORD fileValue = GetFileAttributesA(path.c_str());

    return fileValue < 0xffffffff;
}

void Utility::CreateFolders(string path)
{
    vector<string> folders = SplitString(path,"/");

    string temp = "";

    for (string folder : folders)
    {
        temp += folder + "/";

        if (!ExistDirectory(temp))
            CreateDirectoryA(temp.c_str(), 0);
    }
}
