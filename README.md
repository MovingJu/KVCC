# gh_template

Template repository that enforces **commit, PR and issue conventions** with plain GitHub features and two well-known actions. No code to maintain, nothing to install in your project.

## Use it

1. Click **Use this template**.
2. Apply the settings GitHub does not copy from templates (needs the [GitHub CLI](https://cli.github.com/) and admin rights):

   ```sh
   .github/bootstrap.sh
   ```

Rulesets on private repositories need a paid GitHub plan; public repositories are free.

## What you get

| | |
|---|---|
| Commit messages | [Conventional Commits](https://www.conventionalcommits.org/), checked in every PR by [commitlint](https://github.com/wagoid/commitlint-github-action) (`.github/commitlint.config.json`) |
| PR title | Same format, checked by [action-semantic-pull-request](https://github.com/amannn/action-semantic-pull-request) |
| Merging | Both checks are required; squash only, so the PR title becomes the commit (`.github/rulesets/main.json`) |
| Issues | Bug and feature forms with a pre-filled `fix: ` / `feat: ` title; blank issues disabled |
| PR description | `PULL_REQUEST_TEMPLATE.md` (guidance only) |

The subject can be in any language; only the `type(scope): subject` structure is checked. Issues cannot be blocked at creation, so the forms are guidance.

## Good to know

- The ruleset requires 0 approvals so a solo maintainer can merge. Raise `required_approving_review_count` for teams, then re-run `.github/bootstrap.sh`.
- Required check names must match the job names (`PR title`, `Commit messages`).
- Don't add `paths` filters to these workflows: a skipped workflow leaves a required check pending forever.
- Actions are pinned to SHAs and Dependabot keeps them updated, using a `ci(deps)` prefix so its PRs pass the checks.

See [CONTRIBUTING.md](CONTRIBUTING.md) for the convention.
