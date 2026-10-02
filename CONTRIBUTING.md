# Contributing

Commits, PR titles and issue titles use [Conventional Commits](https://www.conventionalcommits.org/):

```
type(scope)!: subject
```

- `type`: `feat` `fix` `docs` `style` `refactor` `perf` `test` `build` `ci` `chore` `revert`
- `scope` is optional; `!` marks a breaking change
- the subject doesn't start with an uppercase letter or end with a period
- the first line is at most 72 characters; a body goes after a blank line
- reference issues in the PR description or a footer: `Closes #123`

```
feat(auth): add login API
fix: correct payment amount rounding
refactor(core)!: change config loader interface
```

## Flow

1. Open an issue from a template.
2. Branch off the default branch (suggested: `feat/123-login-api`).
3. Open a PR. Its title follows the format above; the description links the issue.
4. When `PR title` and `Commit messages` pass, squash merge. The PR title becomes the commit message.

## Fixing a failed check

- **PR title**: edit it on GitHub; the check re-runs on its own.
- **Commits**: `git commit --amend` or `git rebase -i`, then `git push --force-with-lease`.
