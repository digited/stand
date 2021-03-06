/*
 *
 *    SequenceWindow.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/06/18
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <QScrollBar>
#include <QSlider>

#include "views/NoteView.h"
#include "views/ControlCurveView.h"
#include "views/BeatView.h"
#include "views/TempoView.h"
#include "views/SingerView.h"
#include "views/TrackSelectionView.h"
#include "views/PianoView.h"
#include "views/ControlCurveNameView.h"

#include "models/SequenceModel.h"
#include "models/ControlCurveSelection.h"

#include "controllers/ControlCurveSelector.h"

#include "SequenceWindow.h"
#include "ui_SequenceWindow.h"

SequenceWindow::SequenceWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SequenceWindow)
{
    ui->setupUi(this);

    sequence = new vsq::Sequence("test", 3, 4, 4, 500000);
    vsq::Event e(480 * 4, vsq::EventType::UNKNOWN);
    sequence->updateTotalClocks();
    sequence->track(0)->events()->add(e);
    SequenceModel *model = new SequenceModel(sequence, this);

    ui->Pianoroll->horizontalScrollBar()->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->Pianoroll->verticalScrollBar()->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QSlider *h = new QSlider(Qt::Horizontal, ui->Pianoroll);
    h->setMaximumWidth(80);
    QSlider *v = new QSlider(Qt::Vertical, ui->Pianoroll);
    v->setMaximumHeight(80);
    ui->Pianoroll->addScrollBarWidget(h, Qt::AlignRight);
    ui->Pianoroll->addScrollBarWidget(v, Qt::AlignBottom);

    ui->Pianoroll->setWidget(new NoteView(0, 4, 16, 40, model, ui->Pianoroll));

    ControlCurveSelection *selection = new ControlCurveSelection(1, this);
    selection->mainName = "PIT";
    selection->subNames << "BRI";
    QHash<QString, std::string> labels;
    labels["PIT"] = "pit";
    labels["BRI"] = "bri";
    ControlCurveView *controlView = new ControlCurveView(labels, 0, 4, 40, model, ui->Control);
    controlView->controlCurveSelectionChanged(*selection);
    ui->Control->setWidget(controlView);
    connect(selection, SIGNAL(changeControlCurve(ControlCurveSelection&)), controlView, SLOT(controlCurveSelectionChanged(ControlCurveSelection&)));

    ui->Beat->setWidget(new BeatView(4, 16, 40, model, ui->Beat));
    ui->Tempo->setWidget(new TempoView(4, 16, 40, model, ui->Beat));
    ui->Singer->setWidget(new SingerView(0, 4, 16, 40, model, ui->Beat));
    ui->Piano->setWidget(new PianoView(16, ui->Piano));
    ui->gridLayout->addWidget(new TrackSelectionView(16, model, this), 6, 1, 1, 1);
    QList<QString> names;
    names << "VEL" << "DYN" << "BRI";
    ControlCurveNameView *controlNameView = new ControlCurveNameView(names, 16, this);
    ui->gridLayout->addWidget(controlNameView, 4, 0, 1, 1);
    ControlCurveSelector *selector = new ControlCurveSelector(selection, controlNameView);
    connect(selection, SIGNAL(changeControlCurve(ControlCurveSelection&)), controlNameView, SLOT(selectionChanged(ControlCurveSelection&)));

    connect(ui->Pianoroll->horizontalScrollBar(), SIGNAL(valueChanged(int)), ui->Control->horizontalScrollBar(), SLOT(setValue(int)));
    connect(ui->Pianoroll->horizontalScrollBar(), SIGNAL(valueChanged(int)), ui->Beat->horizontalScrollBar(), SLOT(setValue(int)));
    connect(ui->Pianoroll->horizontalScrollBar(), SIGNAL(valueChanged(int)), ui->Tempo->horizontalScrollBar(), SLOT(setValue(int)));
    connect(ui->Pianoroll->horizontalScrollBar(), SIGNAL(valueChanged(int)), ui->Singer->horizontalScrollBar(), SLOT(setValue(int)));
    connect(ui->Pianoroll->verticalScrollBar(), SIGNAL(valueChanged(int)), ui->Piano->verticalScrollBar(), SLOT(setValue(int)));
    connect(ui->Piano->verticalScrollBar(), SIGNAL(valueChanged(int)), ui->Pianoroll->verticalScrollBar(), SLOT(setValue(int)));
}

SequenceWindow::~SequenceWindow()
{
    delete ui;
}
