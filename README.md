Eltra V1 - JUCE VST3 plugin project (prepared for GitHub Actions)

How to use:
1. Create a new GitHub repository (name it EltraV1).
2. Upload all files and folders from this ZIP to the repository root.
3. Push to the main branch (or use the repository's UI to upload). The workflow will run automatically.
4. After Actions finish, open the Actions tab, select the latest run, and download the artifact "EltraV1-VST3".
5. Extract the .vst3 file and copy it to: C:\Program Files\Common Files\VST3 (on your Windows machine).
6. Open Mixcraft and rescan plugins.

Notes:
- The workflow clones JUCE during CI; you don't need to include JUCE in the repo.
- The built plugin is VST3 only and targets Windows (x64).
- If you need help uploading or running the workflow, send me a screenshot of the Actions page and I'll help debug.