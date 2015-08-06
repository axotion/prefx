#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <fstream>
#include <string.h>
using std::endl;
using std::cout;
using std::ios_base;
using std::cin;
using std::ios;
typedef const std::string static_dump;
typedef std::string dump;
typedef unsigned char uint8_t;
const uint8_t VERSION[12] = "prefx 0.1";
class Choices
{
    public:
    dump choice;
    std::string first_arg;
    void help();
    void laggy();
    void del_cookies();
    void check_files();
    void mplayer_fix();
    void about();
    void sub();
    void ifexist();
    void microphone_test();
};
bool Debug_Permission()
{
    if(geteuid() == 0){throw 0;}
    else{throw 1;}
}
class DEBUG : public Choices
{
    private:
    //static_dump &ref_choice = choice;
    //static_dump *wsk_choice = &choice;
    public:
    DEBUG(dump & _last){
        dump _exit;
        char current[255];
        getcwd(current, 254);
        printf("%c]0;%s%s%c", '33', VERSION, " DEBUG MODE", '07');
        cout << "Path: " << current << endl;
        dump LAST_COMMAND = _last;
        cout << "Version: " << VERSION << endl;
        cout << "User: " << getenv("USER") << endl;
        //cout << "FIRST COMMAND: " << GetFirst << endl;
        cout << "Last command: " << LAST_COMMAND << " "<< LAST_COMMAND.length() << " "<< &LAST_COMMAND <<endl;
        try{
            Debug_Permission();
        }
        catch(int info1){
            if(info1 == 0)
            {
                cout << "With root permission n" ;
            }
            if(info1 == 1)
            {
                cout << "Without root permission n" ;
            }
            cout << "Hit ENTER to continue...";
            while(getchar()!='n');
            printf("%c]0;%s%c", '33', VERSION, '07');
            return;
        }
    }
};
//https://bugs.launchpad.net/linux/+bug/494099
void Choices::sub(){
    if(geteuid() == 0)
    {
        std::fstream sub_write("/etc/pulse/daemon.conf", ios::app );
        sub_write << endl << "enable-lfe-remixing = yes ";
        sub_write.close();
        cout << "And...done!" << endl;
    }
    else{ cout << "33[1;31mThis function must be run as root33[0mn";}
}
void Choices::about(){ cout << "This toolkit has been created by axotion (if you have questions axotion@linux.pl) for pulseaudio(fixes and tweaks c:)";}
void Choices::mplayer_fix()
{
    if(geteuid() == 0){
        std::string _temp_mplayer;
        std::fstream _mplayer;
        _mplayer.open("/etc/mplayer/mplayer.conf", std::ios_base::in );
        if( _mplayer.good() )
        {
            _mplayer >>  _temp_mplayer;
            if(  _temp_mplayer == "ao=pulse")
            {
                cout << "Don't need to fix";
                _temp_mplayer="";
            }
            else
            {
                std::ofstream mplayer;
                mplayer.open ("/etc/mplayer/mplayer.conf");
                mplayer << "ao=pulse";
                mplayer.close();
                cout << "Saved" << endl;
            }
        }
        else { cout << "File doesn't exist "; }
    }
    else { cout << "33[1;31mThis function must be run as root33[0mn"; }
}
void Choices::check_files()
{
    char puls1[25] = "/etc/pulse/client.conf";
    char puls2[25] = "/etc/pulse/daemon.conf";
    std::fstream _puls1;
    std::fstream _puls2;
    _puls1.open(puls1, std::ios_base::in );
    _puls2.open(puls2, std::ios_base::in );
    if(_puls1.good()) { cout << "33[1;32m[OK]33[0m client.conf" << endl; }
    else{ cout << "33[1;31m[Fail]33[0mFile " << puls1 << " not found" << endl;}
    if(_puls2.good()){ cout << "33[1;32m[OK]33[0m daemon.conf"; }
    else{ cout << "33[1;31m[Fail]33[0mFile " << puls2 << " not found";}
}
void Choices::microphone_test(){
    cout << "Say something like `Time and Relative Dimension in Space`n" ;
    system("arecord -f cd -d 5 test-mic.wav>/dev/null 2>&1 ; aplay test-mic.wav>/dev/null 2>&1");
}
void Choices::help()
{
    cout << "help - show available commands 33[1;32m[user]33[0mn";
    cout << "check - verifity files in /etc 33[1;32m[user]33[0mn";
    cout << "mic test - record some mic samples 33[1;32m[user]33[0mn";
    cout << "delete cookies - deleting configuration and cookies 33[1;32m[user]33[0mn";
    cout << "about - some information about toolit 33[1;32m[user]33[0mn";
    cout << "laggy - just fix the lagg sound 33[1;31m[root]33[0mn";
    cout << "subwoofer fix - Subwoofer stops working after end of every song? 33[1;31m[root]33[0mn";
    cout << "mplayer fix - small fix for mplayer(force use PA) 33[1;31m[root]33[0mn";
    cout << "exit - shutdown prefx 33[1;32m[user]33[0mn";
}
void Choices::laggy()
{
    if(geteuid() == 0){
        std::fstream laggy_write("/etc/pulse/daemon.conf", ios::app );
        laggy_write << endl << "default-fragments = 8 ";
        laggy_write << endl <<"default-fragment-size-msec = 5"<< endl;
        laggy_write.close();
    }
    else { cout << "33[1;31mThis function must be run as root33[0mn"; }
}
void Choices::ifexist(){
    std::string yes_or_no;
    std::fstream ifex("/usr/bin/pulseaudio", std::ios::in);
    if(ifex.good());
    else{cout << "33[1;31mI can't see PA, continue? 33[0mn"; getline(cin, yes_or_no); if(yes_or_no=="yes" or yes_or_no=="Yes"); else{exit(0);} };
}
void Choices::del_cookies()
{
    char* path(getenv("HOME"));
    strcat(path,"/.pulse-cookie");
    remove(path);
    strcat(path,"/.pulse");
    remove(path);
}
int main(int argc, char *argv[]){
    printf("%c]0;%s%c", '33', VERSION, '07');
    Choices *_function = new Choices;
    if(argc == 1){
        _function->ifexist();
        cout << VERSION <<" for commands type help";
        while(true){
            cout << endl << ">>> ";
            getline(cin, _function->choice);
            if(_function->choice == "help"){ _function->help(); }
            else if(_function->choice == "laggy"){ _function->laggy(); }
            else if(_function->choice == "delete cookies"){ _function->del_cookies(); }
            else if(_function->choice == "check"){ _function->check_files(); }
            else if(_function->choice == "about"){ _function->about(); }
            else if(_function->choice == "mplayer fix"){ _function->mplayer_fix(); }
            else if(_function->choice == "subwoofer fix"){ _function->sub(); }
            else if(_function->choice == "mic test"){ _function->microphone_test(); }
            else if(_function->choice == "exit"){ ; delete(_function); exit(0); }
            else if(_function->choice == "DEBUG"){ DEBUG(_function->choice); }
            else{  cout << "Command `"<< _function->choice <<"` not found ";}
        }
    }
    else { //running prefx with arguments
        _function->first_arg=argv[1];
        if(_function->first_arg == "--help") { _function->help(); }
        if(_function->first_arg == "--debug") { DEBUG(_function->first_arg); }
    }
}
