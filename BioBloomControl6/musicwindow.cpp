#include "musicwindow.h"
#include "ui_musicwindow.h"

MusicWindow::MusicWindow(BioBloomUnit* inputParentUnit, QWidget *parent) : QWidget(parent), ui(new Ui::MusicWindow), parentUnitAddress(inputParentUnit)
{
    ui->setupUi(this);

    QPalette WindowPalette;                                                                 //Create a palette
    WindowPalette.setColor(QPalette::Background, Qt::white);                               //Configure the palette to fill the background with white
    this->setPalette(WindowPalette);                                                      //Set the palette

    volume = 15;
    QString volumeString;
    volumeString.setNum(volume);
    ui->VolumeLabel->setText(volumeString);

    setupSongList();
    setupPushButtonFunctions();





    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));

    QUrl url;
    QByteArray postData;

    url.setUrl("http://192.168.5.1:80/audio_request.php");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    QString postKey = "mac";
    QString postValue = parentUnitAddress->getMacAddress();
    QString postKey2 = "volume";
    QString postValue2 = "insert volume here";
    QString postKey3 = "track";
    QString postValue3 = "insert track here";

    postData.append(postKey).append("=").append(postValue).append("&").append(postKey2).append("=").append(postValue2).append("&").append(postKey3).append("=").append(postValue3).append("&");
    manager->post(request,postData);

    //1 for first track
    //2 for second track etc.
    // will agree on a system so we know exactly what files correspond to each number
    //params.addQueryItem("volume_id", "...");
    //number between 0 and 30 //0 being mute
    //this could be based from a volume slider?
    //would also need volume change added as an action if the volume is altered during a sound effect?
    //depends how long the effects are?

}

MusicWindow::~MusicWindow()
{
    delete ui;
}

/*              Class Slots                 */
void MusicWindow::backButtonPressSlot()
{
    this->close();
}

void MusicWindow::volumeUpButtonPressSlot()
{
    if(volume < 30)
        ++volume;

    QString volumeString;
    volumeString.setNum(volume);
    ui->VolumeLabel->setText(volumeString);
}

void MusicWindow::volumeDownButtonPressSlot()
{
    if(volume > 0)
        --volume;

    QString volumeString;
    volumeString.setNum(volume);
    ui->VolumeLabel->setText(volumeString);
}

void MusicWindow::pauseButtonPressSlot()
{
    if(pauseFlag == 0)
        pauseFlag = 1;
                //pause

    else
        pauseFlag = 0;
        //play
}

void MusicWindow::Track1ButtonPressSlot()
{

}

void MusicWindow::Track2ButtonPressSlot()
{

}

void MusicWindow::Track3ButtonPressSlot()
{

}

void MusicWindow::Track4ButtonPressSlot()
{

}

void MusicWindow::Track5ButtonPressSlot()
{

}

void MusicWindow::Track6ButtonPressSlot()
{

}

void MusicWindow::Track7ButtonPressSlot()
{

}

void MusicWindow::Track8ButtonPressSlot()
{

}

void MusicWindow::Track9ButtonPressSlot()
{

}

void MusicWindow::Track10ButtonPressSlot()
{

}

void MusicWindow::Track11ButtonPressSlot()
{

}

/*              Class Methods               */
void MusicWindow::setupSongList()
{
    songButtonAddress.append(new QPushButton(this));
    songButtonAddress[0]->setText("1.   Ave Maris Stella            Monteverdi Maria Vespers");

    songItemAddress.append(new QListWidgetItem(ui->SongList));

    songItemAddress[0]->setSizeHint(songButtonAddress[0]->size());
    ui->SongList->setItemWidget(songItemAddress[0], songButtonAddress[0]);
    ui->SongList->addItem(songItemAddress[0]);

    connect(songButtonAddress[0], SIGNAL(released()), this, SLOT(Track1ButtonPressSlot()) );



    songButtonAddress.append(new QPushButton(this));
    songButtonAddress[1]->setText("2.   Piano Concerto #21 in C, Andante            Mozart");

    songItemAddress.append(new QListWidgetItem(ui->SongList));

    songItemAddress[1]->setSizeHint(songButtonAddress[1]->size());
    ui->SongList->setItemWidget(songItemAddress[1], songButtonAddress[1]);
    ui->SongList->addItem(songItemAddress[1]);

    connect(songButtonAddress[1], SIGNAL(released()), this, SLOT(Track2ButtonPressSlot()) );



    songButtonAddress.append(new QPushButton(this));
    songButtonAddress[2]->setText("3.   Symphony #41 In C,  Jupiter  Finale   Molto Allegro           Mozart");

    songItemAddress.append(new QListWidgetItem(ui->SongList));

    songItemAddress[2]->setSizeHint(songButtonAddress[2]->size());
    ui->SongList->setItemWidget(songItemAddress[2], songButtonAddress[2]);
    ui->SongList->addItem(songItemAddress[2]);

    connect(songButtonAddress[2], SIGNAL(released()), this, SLOT(Track3ButtonPressSlot()) );



    songButtonAddress.append(new QPushButton(this));
    songButtonAddress[3]->setText("4.   Symphony no6 (Pathetique) Karajan movt 2            Tchaikovsky");

    songItemAddress.append(new QListWidgetItem(ui->SongList));

    songItemAddress[3]->setSizeHint(songButtonAddress[3]->size());
    ui->SongList->setItemWidget(songItemAddress[3], songButtonAddress[3]);
    ui->SongList->addItem(songItemAddress[3]);

    connect(songButtonAddress[3], SIGNAL(released()), this, SLOT(Track4ButtonPressSlot()) );



    songButtonAddress.append(new QPushButton(this));
    songButtonAddress[4]->setText("5.   Fur Elise            Mozart");

    songItemAddress.append(new QListWidgetItem(ui->SongList));

    songItemAddress[4]->setSizeHint(songButtonAddress[4]->size());
    ui->SongList->setItemWidget(songItemAddress[4], songButtonAddress[4]);
    ui->SongList->addItem(songItemAddress[4]);

    connect(songButtonAddress[4], SIGNAL(released()), this, SLOT(Track5ButtonPressSlot()) );



    songButtonAddress.append(new QPushButton(this));
    songButtonAddress[5]->setText("6.   Symphony No.7, Op. 92            Beethoven");

    songItemAddress.append(new QListWidgetItem(ui->SongList));

    songItemAddress[5]->setSizeHint(songButtonAddress[5]->size());
    ui->SongList->setItemWidget(songItemAddress[5], songButtonAddress[5]);
    ui->SongList->addItem(songItemAddress[5]);

    connect(songButtonAddress[5], SIGNAL(released()), this, SLOT(Track6ButtonPressSlot()) );



    songButtonAddress.append(new QPushButton(this));
    songButtonAddress[6]->setText("7.   Symphony No.5 Op. 67            Beethoven");

    songItemAddress.append(new QListWidgetItem(ui->SongList));

    songItemAddress[6]->setSizeHint(songButtonAddress[6]->size());
    ui->SongList->setItemWidget(songItemAddress[6], songButtonAddress[6]);
    ui->SongList->addItem(songItemAddress[6]);

    connect(songButtonAddress[6], SIGNAL(released()), this, SLOT(Track7ButtonPressSlot()) );



    songButtonAddress.append(new QPushButton(this));
    songButtonAddress[7]->setText("8.   The Valkyrie: Rise of the Valkyries           Wagner");

    songItemAddress.append(new QListWidgetItem(ui->SongList));

    songItemAddress[7]->setSizeHint(songButtonAddress[7]->size());
    ui->SongList->setItemWidget(songItemAddress[7], songButtonAddress[7]);
    ui->SongList->addItem(songItemAddress[7]);

    connect(songButtonAddress[7], SIGNAL(released()), this, SLOT(Track8ButtonPressSlot()) );



    songButtonAddress.append(new QPushButton(this));
    songButtonAddress[8]->setText("9.   Requiem, K.626: Lacrimosa Dies Illa           Mozart");

    songItemAddress.append(new QListWidgetItem(ui->SongList));

    songItemAddress[8]->setSizeHint(songButtonAddress[8]->size());
    ui->SongList->setItemWidget(songItemAddress[8], songButtonAddress[8]);
    ui->SongList->addItem(songItemAddress[8]);

    connect(songButtonAddress[8], SIGNAL(released()), this, SLOT(Track9ButtonPressSlot()) );



    songButtonAddress.append(new QPushButton(this));
    songButtonAddress[9]->setText("10.   Le nozze di Figaro: Sinfonia           Mozart");

    songItemAddress.append(new QListWidgetItem(ui->SongList));

    songItemAddress[9]->setSizeHint(songButtonAddress[9]->size());
    ui->SongList->setItemWidget(songItemAddress[9], songButtonAddress[9]);
    ui->SongList->addItem(songItemAddress[9]);

    connect(songButtonAddress[9], SIGNAL(released()), this, SLOT(Track10ButtonPressSlot()) );



    songButtonAddress.append(new QPushButton(this));
    songButtonAddress[10]->setText("11.   Cello Suite No.1             Bach");

    songItemAddress.append(new QListWidgetItem(ui->SongList));

    songItemAddress[10]->setSizeHint(songButtonAddress[10]->size());
    ui->SongList->setItemWidget(songItemAddress[10], songButtonAddress[10]);
    ui->SongList->addItem(songItemAddress[10]);

    connect(songButtonAddress[10], SIGNAL(released()), this, SLOT(Track11ButtonPressSlot()) );
}


void MusicWindow::setupPushButtonFunctions()
{
   connect(ui->BackButton, SIGNAL(released()), this, SLOT(backButtonPressSlot()) );
   connect(ui->VolumeUp, SIGNAL(released()), this, SLOT(volumeUpButtonPressSlot()) );
   connect(ui->VolumeDown, SIGNAL(released()), this, SLOT(volumeDownButtonPressSlot()) );
   connect(ui->PlayPauseButton, SIGNAL(released()), this, SLOT(pauseButtonPressSlot()) );
}
