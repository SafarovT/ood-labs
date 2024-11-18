#pragma once
#include <list>
#include <vector>
#include "IDocument.h"
#include "CUndoManager.h"

class CDocument : public IDocument
{
public:
    CDocument() {};
    void InsertParagraph(const std::string& text, std::optional<size_t> position = std::nullopt) override;
    void InsertImage(const std::string& path, int width, int height, std::optional<size_t> position = std::nullopt) override;
    size_t GetItemsCount()const override;
    CConstDocumentItem GetItem(size_t index)const override;
    CDocumentItem GetItem(size_t index) override;
    std::string GetTitle()const override;
    void DeleteItem(size_t index) override;
    void SetTitle(const std::string& title) override;
    bool CanUndo()const override;
    void Undo() override;
    bool CanRedo()const override;
    void Redo() override;
    void List() const override;
    void Save(const std::string& path) const override;

private:
    CDocument(const CDocument&) {};
    CDocument& operator=(const CDocument&) {};

    void CheckElementAtIndex(size_t index) const;
    void CheckOverflowBeforeInsert() const;
    std::vector<CDocumentItem>::iterator GetIterAtIndex(size_t index);

    std::string m_title;
    std::vector<CDocumentItem> m_items;
    CUndoManager m_history;
};

