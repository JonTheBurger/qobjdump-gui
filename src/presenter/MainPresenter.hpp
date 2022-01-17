#pragma once

#include <QObject>
#include <memory>

class ElfFile;
class QAbstractItemModel;
class SectionHeaderItemModel;
class SettingsPresenter;
class SymbolTableItemModel;

class MainPresenter final : public QObject {
  Q_OBJECT
  Q_DISABLE_COPY(MainPresenter)

public:
  MainPresenter(SectionHeaderItemModel& section_header_item_model,
                SettingsPresenter&      settings_presenter,
                SymbolTableItemModel&   symbol_table_item_model,
                QObject*                parent = nullptr);
  ~MainPresenter() override;

  SectionHeaderItemModel& sectionHeaderItemModel() noexcept;
  QAbstractItemModel&     sectionHeaderDisplayModel() noexcept;
  QAbstractItemModel&     sectionHeaderCheckedModel() noexcept;

  SymbolTableItemModel& symbolTableItemModel() noexcept;
  QAbstractItemModel&   symbolTableDisplayModel() noexcept;
  QAbstractItemModel&   symbolTableCheckedModel() noexcept;

  SettingsPresenter& settingsPresenter() noexcept;

private:
  struct Impl;
  std::unique_ptr<Impl> _self;
};
