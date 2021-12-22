#include "MainWindow.hpp"

#include <DockManager.h>
#include <QPlainTextEdit>
#include <spdlog/sinks/qt_sinks.h>
#include <spdlog/spdlog.h>

#include "HexView.hpp"
#include "MultiFilterTableView.hpp"
#include "PieChartForm.hpp"
#include "SettingsForm.hpp"
#include "presenter/MainPresenter.hpp"
#include "presenter/SectionHeaderItemModel.hpp"
#include "presenter/SymbolTableItemModel.hpp"
#include "ui_MainWindow.h"

struct MainWindow::Impl {
  Q_DISABLE_COPY(Impl)

  MainWindow&          self;
  Ui::MainWindow       ui;
  MainPresenter&       presenter;
  ads::CDockManager*   dock;
  QItemSelectionModel* symsel;
  QItemSelectionModel* secsel;

  explicit Impl(MainWindow& that, MainPresenter& present) noexcept
      : self{ that }
      , ui{}
      , presenter{ present }
      , dock{}
  {
    ui.setupUi(&self);
    // Dock constructor must come AFTER setupUi()
    dock = new ads::CDockManager(&self);
    dock->setConfigFlag(ads::CDockManager::FloatingContainerForceNativeTitleBar, true);
  }

  /// Takes ownership of widget
  void addDock(const QString& name, QWidget* widget, ads::DockWidgetArea location = ads::TopDockWidgetArea)
  {
    auto* dock_widget = new ads::CDockWidget(name);
    dock_widget->setWidget(widget);
    dock->addDockWidget(location, dock_widget);
    ui.menu_view->addAction(dock_widget->toggleViewAction());
  }

  /// Takes ownership of widget
  void addDockTab(const QString& name, QWidget* widget, ads::DockWidgetArea location = ads::TopDockWidgetArea)
  {
    auto* dock_widget = new ads::CDockWidget(name);
    dock_widget->setWidget(widget);
    dock->addDockWidgetTab(location, dock_widget);
    ui.menu_view->addAction(dock_widget->toggleViewAction());
  }

  void initSettingsDock()
  {
    auto* widget = new SettingsForm(presenter.settingsPresenter(), &self);
    addDock("Settings", widget, ads::TopDockWidgetArea);
  }

  void initLogOutputDock()
  {
    auto* widget          = new QPlainTextEdit();
    auto  widget_log_sink = std::make_shared<spdlog::sinks::qt_sink_mt>(widget, "appendPlainText");
    spdlog::get("")->sinks().push_back(std::move(widget_log_sink));
    addDock("Log Output", widget, ads::BottomDockWidgetArea);
  }

  void initSectionHeaderDock()
  {
    auto* widget = new MultiFilterTableView(&self);
    widget->setModel(&presenter.sectionHeaderItemModel());
    secsel = widget->selectionModel();
    addDockTab("Section Headers", widget, ads::BottomDockWidgetArea);
  }

  void initSymbolTableDock()
  {
    auto* widget = new MultiFilterTableView(&self);
    widget->setModel(&presenter.symbolTableItemModel());
    symsel = widget->selectionModel();
    addDockTab("Symbol Table", widget, ads::BottomDockWidgetArea);
  }

  void initSectionHeaderChartDock()
  {
    auto* widget = new PieChartForm(presenter.selectedSectionHeaderItemModel(),
                                    SectionHeaderItemModel::NAME,
                                    SectionHeaderItemModel::SIZE,
                                    &self);
    addDockTab("Section Headers", widget, ads::TopDockWidgetArea);
  }

  void initSymbolTableChartDock()
  {
    auto* widget = new PieChartForm(presenter.selectedSymbolTableItemModel(),
                                    SymbolTableItemModel::DEMANGLED_NAME,
                                    SymbolTableItemModel::SIZE,
                                    &self);
    symsel->connect(symsel, &QItemSelectionModel::selectionChanged, [this, widget](const QItemSelection& selected, const QItemSelection& deselected) {
      if (!selected.indexes().empty())
      {
        auto idx = selected.indexes()[0].row();
      }
      else
      {
      }
    });
    addDockTab("Symbol Table", widget, ads::TopDockWidgetArea);
  }

  void initSectionHeaderHexDock()
  {
    auto* widget = new HexView(&self);
    addDockTab("Section Contents", widget, ads::TopDockWidgetArea);
  }

  void initSymbolTableHexDock()
  {
    auto* widget = new HexView(&self);
    addDockTab("Disassembly", widget, ads::TopDockWidgetArea);
  }
};

MainWindow::MainWindow(MainPresenter& present, QWidget* parent)
    : QMainWindow(parent)
    , _self{ std::make_unique<Impl>(*this, present) }
{
  _self->initSettingsDock();
  _self->initLogOutputDock();
  _self->initSectionHeaderDock();
  _self->initSymbolTableDock();
  _self->initSectionHeaderChartDock();
  _self->initSectionHeaderHexDock();
  _self->initSymbolTableChartDock();
  _self->initSymbolTableHexDock();
}

MainWindow::~MainWindow() = default;
