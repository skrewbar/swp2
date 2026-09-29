-- Loaded only when neovim starts in this repo (lazy.nvim local_spec).
-- First open: view this file, then run `:trust` so it can execute.
-- Treat Arduino sketches as C++ so LazyVim clangd attaches.
vim.filetype.add({ extension = { ino = "cpp" } })

return {}
